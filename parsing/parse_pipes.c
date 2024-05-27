/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:54:04 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/27 19:17:04 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE_TKN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_token	*get_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE_TKN)
			return (tmp->next);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_token(t_token **token, t_token *pipeless)
{
	t_token	*tmp;

	tmp = *token;
	if (!tmp)
	{
		*token = malloc(sizeof(t_token));
		(*token)->data = ft_strdup(pipeless->data);
		(*token)->type = pipeless->type;
		(*token)->state = pipeless->state;
		(*token)->next = NULL;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = pipeless;
	tmp->next->next = NULL;
}

t_token	*remove_pipe(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp2;
	t_token	*pipeless;

	tmp = token;
	pipeless = NULL;
	while (tmp)
	{
		if (tmp->type == PIPE_TKN)
		{
			tmp2 = tmp->next;
			remove_token(&token, tmp);
			return (pipeless);
		}
		add_token(&pipeless, tmp);
		tmp = tmp->next;
	}
	return (pipeless);
}

void	parse_pipes(t_prompt **prmpt, t_token **token, t_env *env)
{
	t_token	*tmp;
	t_token	*pipeless;

	print_tokens(*token);
	if (!check_pipe(*token))
	{
		(*prmpt)->left = NULL;
		(*prmpt)->right = NULL;
		(*prmpt)->type = P_CMD;
		(*prmpt)->cmd = parse_cmd(*token, env);
		return ;
	}
	tmp = get_pipe(*token);
	pipeless = remove_pipe(*token);
	(*prmpt)->left = malloc(sizeof(t_prompt));
	(*prmpt)->right = malloc(sizeof(t_prompt));
	parse_pipes(&(*prmpt)->left, &pipeless, env);
	parse_pipes(&(*prmpt)->right, &tmp, env);
	(*prmpt)->type = P_PIPE;
}
