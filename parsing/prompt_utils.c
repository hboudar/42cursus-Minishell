/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:19:22 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 09:19:23 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_and_or(t_token *token)
{
	while (token)
	{
		if (token->type == AND_TOKEN || token->type == OR_TOKEN)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int	check_and_or_limit(t_token *token, t_token *limit)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp != limit)
	{
		if (tmp->type == AND_TOKEN || tmp->type == OR_TOKEN
			|| tmp->type == PIPE_TKN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_and_or(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == OPENPAR)
			tmp = get_closepar(tmp);
		if (tmp->type == AND_TOKEN || tmp->type == OR_TOKEN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	remove_redirections_subshell(t_token **token, t_token *limit)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	while (tmp && tmp != limit)
	{
		if (tmp->type == REDIR_HERE_DOC || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_IN || tmp->type == APPEND)
		{
			remove_token(token, tmp->next);
			tmp2 = tmp->next;
			remove_token(token, tmp);
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
}

void	handle_subshells(t_prompt **prmpt, t_token **token, t_token *limit)
{
	t_token	*tmp;

	(*prmpt)->type = (limit->type == AND_TOKEN) * P_AND
		+ (limit->type == OR_TOKEN) * P_OR + (limit->type == PIPE_TKN) * P_PIPE;
	(*prmpt)->left = malloc(sizeof(t_prompt));
	ft_bzero((*prmpt)->left, sizeof(t_prompt));
	(*prmpt)->left->subshell = 1;
	(*prmpt)->right = malloc(sizeof(t_prompt));
	ft_bzero((*prmpt)->right, sizeof(t_prompt));
	fill_redirections_sub((*prmpt)->left, *token, limit);
	remove_redirections_subshell(token, limit);
	split_token(*token, limit, &tmp);
	build_prompt(&(*prmpt)->left, &tmp);
	free_token_limit(token, limit->next);
	build_prompt(&(*prmpt)->right, token);
}
