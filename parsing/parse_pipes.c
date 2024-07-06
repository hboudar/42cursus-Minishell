/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:54:04 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/14 12:09:39 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_subshell_pipe(t_prompt **prmpt, t_token **token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	tmp2 = get_closepar(tmp);
	remove_token(token, tmp);
	remove_token(token, tmp2);
	(*prmpt)->subshell = 1;
	build_prompt(prmpt, token);
}

void	end_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp && tmp->next)
	{
		if (tmp->next->data == NULL && !tmp->next->next)
		{
			free(tmp->next);
			tmp->next = NULL;
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
		if (tmp->type == OPENPAR)
			tmp = get_closepar(tmp);
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

void	parse_pipes(t_prompt **prmpt, t_token **token)
{
	t_token	*tmp;
	t_token	*pipeless;

	if ((*token)->type == OPENPAR)
	{
		handle_subshell_pipe(prmpt, token);
		return ;
	}
	if (!check_pipe(*token))
	{
		set_size(*token);
		(*prmpt)->cmd = parse_cmd(*prmpt, token);
		return ;
	}
	tmp = get_pipe(token);
	split_token(*token, tmp, &pipeless);
	(*prmpt)->left = malloc(sizeof(t_prompt));
	ft_bzero((*prmpt)->left, sizeof(t_prompt));
	(*prmpt)->right = malloc(sizeof(t_prompt));
	ft_bzero((*prmpt)->right, sizeof(t_prompt));
	parse_pipes(&(*prmpt)->left, &pipeless);
	free_token_limit(token, tmp);
	parse_pipes(&(*prmpt)->right, &tmp);
	(*prmpt)->type = P_PIPE;
}
