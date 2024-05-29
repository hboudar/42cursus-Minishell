/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:54:04 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/29 12:48:29 by aoulahra         ###   ########.fr       */
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

t_token	*get_pipe(t_token **token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == PIPE_TKN)
		{
			tmp2 = tmp->next;
			remove_token(token, tmp);
			return (tmp2);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	parse_pipes(t_prompt **prmpt, t_token **token, t_env *env)
{
	t_token	*tmp;
	t_token	*pipeless;

	print_tokens(*token);
	if (!check_pipe(*token))
	{
		set_size(*token);
		set_state(*token);
		(*prmpt)->left = NULL;
		(*prmpt)->right = NULL;
		(*prmpt)->type = P_CMD;
		(*prmpt)->cmd = parse_cmd(*token, env);
		return ;
	}
	tmp = get_pipe(token);
	split_token(*token, tmp, &pipeless);
	print_tokens(pipeless);
	print_tokens(tmp);
	(*prmpt)->left = malloc(sizeof(t_prompt));
	ft_bzero((*prmpt)->left, sizeof(t_prompt));
	(*prmpt)->right = malloc(sizeof(t_prompt));
	ft_bzero((*prmpt)->right, sizeof(t_prompt));
	parse_pipes(&(*prmpt)->left, &pipeless, env);
	parse_pipes(&(*prmpt)->right, &tmp, env);
	(*prmpt)->type = P_PIPE;
}
