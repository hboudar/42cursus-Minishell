/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:34:17 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/06 22:20:33 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_token(t_token **token, t_token *node)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	tmp2 = NULL;
	while (tmp != node)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (tmp2)
			tmp2->next = tmp->next;
		else
			*token = tmp->next;
		free(tmp->data);
		free(tmp);
	}
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

t_token	**split_token(t_token *token, t_token *split)
{
	t_token	*tmp;
	t_token	*new_token;
	t_token	**res;

	new_token = (t_token *)malloc(sizeof(t_token));
	ft_bzero(new_token, sizeof(t_token));
	tmp = new_token;
	while (token != split)
	{
		tmp->data = ft_strdup(token->data);
		tmp->size = token->size;
		tmp->type = token->type;
		tmp->state = token->state;
		tmp->next = (t_token *)malloc(sizeof(t_token));
		ft_bzero(tmp->next, sizeof(t_token));
		tmp = tmp->next;
		token = token->next;
	}
	res = &new_token;
	return (res);
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
	printf("Parsed prompt\n");
	print_tokens(token);
	return (prmpt);
}
