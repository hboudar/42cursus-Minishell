/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:18:11 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 09:18:12 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	handle_par(t_prompt **prmpt, t_token **token, t_token *tmp)
{
	t_token	*tmp2;

	tmp2 = get_closepar(tmp);
	remove_token(token, tmp);
	tmp = tmp2->next;
	remove_token(token, tmp2);
	tmp2 = *token;
	if (check_and_or(tmp) || has_pipe(tmp))
		handle_subshells(prmpt, token, get_limit(tmp));
	else
	{
		while (tmp2->next != tmp)
			tmp2 = tmp2->next;
		if (check_and_or_limit(*token, tmp))
			(*prmpt)->subshell = 1;
		fill_redirections_sub(*prmpt, tmp, NULL);
		remove_redirections_subshell(&tmp2, NULL);
		build_prompt(prmpt, token);
	}
}

void	build_prompt(t_prompt **prmpt, t_token **token)
{
	t_token	*tmp;
	t_token	*res;

	tmp = *token;
	if (tmp && tmp->type == OPENPAR)
		handle_par(prmpt, token, tmp);
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
		tmp = tmp->next;
		free_token_limit(token, tmp);
		build_prompt(&(*prmpt)->right, &tmp);
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
		prmpt->exit_state = (*oldprmpt)->exit_state * (1 - g_caught) + g_caught;
		free_prompt(oldprmpt);
		*oldprmpt = prmpt;
	}
	else
		prmpt->exit_state = g_caught;
	g_caught = 0;
	if (check_syntax_bonus(token) || check_syntax(token))
	{
		printf("Syntax error\n");
		prmpt->exit_state = 300;
		free_token(&token);
	}
	else
		build_prompt(&prmpt, &token);
	*oldprmpt = prmpt;
}
