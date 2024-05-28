/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:54:04 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/28 20:45:40 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	end_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp && tmp->next)
	{
		if (tmp->next->data == NULL)
		{
			remove_token(token, tmp->next);
			break ;
		}
		tmp = tmp->next;
	}
}

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

void	parse_pipes(t_prompt **prmpt, t_token **token, t_env *env)
{
	t_token	*tmp;
	t_token	**pipeless;

	if (!check_pipe(*token))
	{
		end_token(token);
		set_size(*token);
		set_state(*token);
		(*prmpt)->left = NULL;
		(*prmpt)->right = NULL;
		(*prmpt)->type = P_CMD;
		(*prmpt)->cmd = parse_cmd(*token, env);
		return ;
	}
	tmp = get_pipe(*token);
	pipeless = split_token(*token, tmp);
	(*prmpt)->left = malloc(sizeof(t_prompt));
	(*prmpt)->right = malloc(sizeof(t_prompt));
	parse_pipes(&(*prmpt)->left, pipeless, env);
	parse_pipes(&(*prmpt)->right, &tmp, env);
	(*prmpt)->type = P_PIPE;
}
