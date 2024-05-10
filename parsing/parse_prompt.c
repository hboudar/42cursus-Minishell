/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:34:17 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/10 09:38:34 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		if (!tmp2)
		{
			printf("Syntax error\n");
			return ;
		}
		remove_token(token, tmp);
		tmp = tmp2->next;
		remove_token(token, tmp2);
		if (!check_and_or_pipe(tmp))
		{
			build_prompt(prmpt, token, env);
			return ;
		}
	}
	if (check_and_or_pipe(*token))
	{
		tmp = get_and_or_pipe(*token);
		(*prmpt)->type = (tmp->type == AND_TOKEN) * P_AND
			+ (tmp->type == OR_TOKEN) * P_OR
			+ (tmp->type == PIPE_TKN) * P_PIPE;
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

t_prompt	*parse_prompt(char *line, t_env *env)
{
	t_prompt	*prmpt;
	t_token		*token;

	token = parse_token(line);
	if (!token)
		return (NULL);
	prmpt = (t_prompt *)malloc(sizeof(t_prompt));
	ft_bzero(prmpt, sizeof(t_prompt));
	build_prompt(&prmpt, &token, env);
	return (prmpt);
}
