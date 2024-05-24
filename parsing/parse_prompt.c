/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:34:17 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/24 16:03:18 by aoulahra         ###   ########.fr       */
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

void	build_prompt(t_prompt **prmpt, t_token **token, t_env *env)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	if (tmp && tmp->type == OPENPAR)
	{
		tmp2 = get_closepar(tmp);
		remove_token(token, tmp);
		tmp = tmp2->next;
		remove_token(token, tmp2);
		if (!check_and_or(tmp))
		{
			build_prompt(prmpt, token, env);
			return ;
		}
	}
	if (check_and_or(*token))
	{
		tmp = get_and_or(*token);
		(*prmpt)->type = (tmp->type == AND_TOKEN) * P_AND
			+ (tmp->type == OR_TOKEN) * P_OR;
		(*prmpt)->left = (t_prompt *)malloc(sizeof(t_prompt));
		ft_bzero((*prmpt)->left, sizeof(t_prompt));
		(*prmpt)->right = (t_prompt *)malloc(sizeof(t_prompt));
		ft_bzero((*prmpt)->right, sizeof(t_prompt));
		build_prompt(&(*prmpt)->left, split_token(*token, tmp), env);
		build_prompt(&(*prmpt)->right, &tmp->next, env);
	}
	else
	{
		(*prmpt)->type = P_CMD;
		(*prmpt)->cmd = parse_cmd(*token, env);
		(*prmpt)->left = NULL;
		(*prmpt)->right = NULL;
	}
}

void	parse_prompt(t_prompt **oldprmpt , char *line, t_env *env)
{
	t_prompt	*prmpt;
	t_token		*token;

	prmpt = (t_prompt *)malloc(sizeof(t_prompt));
	ft_bzero(prmpt, sizeof(t_prompt));
	token = parse_token(line, env);
	if (!token && set_exit_state(oldprmpt, prmpt))
		return ;
	if (*oldprmpt)
	{
		prmpt->exit_state = (*oldprmpt)->exit_state;
		free_prompt(oldprmpt);
		*oldprmpt = prmpt;
	}
	if (check_syntax_bonus(token) || check_syntax(token))
	{
		printf("Syntax error\n");
		prmpt->exit_state = 300;
		*oldprmpt = prmpt;
		free_token(token);
		return ;
	}
	build_prompt(&prmpt, &token, env);	
	*oldprmpt = prmpt;
}
