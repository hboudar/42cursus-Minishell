/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:34:17 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/06 19:06:58 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	set_exit_state(t_prompt **oldprmpt, t_prompt *prmpt)
{
	if (*oldprmpt)
	{
		prmpt->exit_state = (*oldprmpt)->exit_state;
		free_prompt(oldprmpt);
		*oldprmpt = prmpt;
	}
	else
	{
		prmpt->exit_state = 300;
		*oldprmpt = prmpt;
	}
	return (1);
}

t_token	*get_closepar(t_token *token)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == OPENPAR)
			count++;
		else if (tmp->type == CLOSEPAR)
			count--;
		if (count == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	handle_par(t_prompt **prmpt, t_token **token, t_token *tmp, t_token *tmp2)
{
	tmp2 = get_closepar(tmp);
	remove_token(token, tmp);
	tmp = tmp2->next;
	remove_token(token, tmp2);
	(1) && (tmp2 = tmp, tmp = *token);
	(*prmpt)->subshell = 1;
	if (!check_and_or(tmp))
		build_prompt(prmpt, token);
	else
	{
		fill_redirections_subshell(*prmpt, tmp2);
		remove_redirections(&tmp2);
		tmp2 = get_and_or(tmp);
		(*prmpt)->type = (tmp2->type == AND_TOKEN) * P_AND
			+ (tmp2->type == OR_TOKEN) * P_OR;
		(*prmpt)->left = (t_prompt *)malloc(sizeof(t_prompt));
		ft_bzero((*prmpt)->left, sizeof(t_prompt));
		(*prmpt)->right = (t_prompt *)malloc(sizeof(t_prompt));
		ft_bzero((*prmpt)->right, sizeof(t_prompt));
		split_token(*token, tmp2, &tmp);
		build_prompt(&(*prmpt)->left, &tmp);
		build_prompt(&(*prmpt)->right, &tmp2->next);
	}
}

void	build_prompt(t_prompt **prmpt, t_token **token)
{
	t_token	*tmp;
	t_token	*res;

	tmp = *token;
	if (tmp && tmp->type == OPENPAR)
		handle_par(prmpt, token, tmp, NULL);
	else if (check_and_or(*token))
	{
		tmp = *token;
		tmp = get_and_or(tmp);
		(*prmpt)->type = (tmp->type == AND_TOKEN) * P_AND
			+ (tmp->type == OR_TOKEN) * P_OR;
		(*prmpt)->left = (t_prompt *)malloc(sizeof(t_prompt));
		ft_bzero((*prmpt)->left, sizeof(t_prompt));
		(*prmpt)->right = (t_prompt *)malloc(sizeof(t_prompt));
		ft_bzero((*prmpt)->right, sizeof(t_prompt));
		split_token(*token, tmp, &res);
		build_prompt(&(*prmpt)->left, &res);
		build_prompt(&(*prmpt)->right, &tmp->next);
	}
	else
		parse_pipes(prmpt, token);
}

void	parse_prompt(t_prompt **oldprmpt, char *line)
{
	t_prompt	*prmpt;
	t_token		*token;
	extern int	g_caught;

	prmpt = (t_prompt *)malloc(sizeof(t_prompt));
	ft_bzero(prmpt, sizeof(t_prompt));
	token = parse_token(line);
	if (!token && set_exit_state(oldprmpt, prmpt))
		return ;
	if (*oldprmpt)
	{
		prmpt->exit_state = ((*oldprmpt)->exit_state) * (1 - g_caught);
		free_prompt(oldprmpt);
		*oldprmpt = prmpt;
	}
	if (check_syntax_bonus(token) || check_syntax(token))
	{
		printf("Syntax error\n");
		prmpt->exit_state = 300;
		*oldprmpt = prmpt;
		free_token(&token);
		return ;
	}
	build_prompt(&prmpt, &token);
	*oldprmpt = prmpt;
}
