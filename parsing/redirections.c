/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:20:56 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/20 16:33:41 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_limiter(t_limiter **limiters, char *arg, int state)
{
	t_limiter	*new;
	t_limiter	*tmp;

	new = (t_limiter *)malloc(sizeof(t_limiter));
	ft_bzero(new, sizeof(t_limiter));
	if (!new)
		exit(1);
	new->limit = ft_strdup(arg);
	new->quotes = state;
	tmp = *limiters;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*limiters = new;
}

void	add_limiters(t_limiter **limiter, t_token *token, int state)
{
	t_limiter	*new;
	t_limiter	*tmp;

	(1) && (new = (t_limiter *)malloc(sizeof(t_limiter)), tmp = *limiter);
	ft_bzero(new, sizeof(t_limiter));
	if (!new)
		exit(1);
	if (!token->joinable)
	{
		addback_data(&new->args, token->data, token->state, token->joinable);
		new->quotes = state;
	}
	while (token && token->joinable)
	{
		addback_data(&new->args, token->data, token->state, token->joinable);
		if (token->state == IN_SQUOTES || token->state == IN_DQUOTES)
			new->quotes = token->state;
		else if (!new->quotes)
			new->quotes = state;
		token = token->next;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	(*limiter) && (tmp->next = new);
	(!*limiter) && (*limiter = new);
}

void	remove_redirections(t_token **token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APPEND || tmp->type == REDIR_HERE_DOC)
		{
			if (!tmp->next->joinable)
			{
				tmp2 = tmp->next;
				remove_token(token, tmp2);
			}
			while (tmp->next && tmp->next->joinable)
			{
				tmp2 = tmp->next;
				remove_token(token, tmp2);
			}
			tmp2 = tmp->next;
			(1) && (remove_token(token, tmp), tmp = tmp2);
		}
		else if (tmp)
			tmp = tmp->next;
	}
}

void	fill_redirections(t_cmd *cmd, t_token *token)
{
	while (token)
	{
		if (token->type == REDIR_IN)
			ft_fileaddback(&(cmd->file),
				ft_newfiles(&token, 0, token->next->state));
		else if (token->type == REDIR_OUT || token->type == APPEND)
			ft_fileaddback(&(cmd->file),
				ft_newfiles(&token,
					1 + (token->type == APPEND), token->next->state));
		else if (token->type == REDIR_HERE_DOC)
		{
			add_limiters(&cmd->limiter, token->next, token->next->state);
			join_limit(cmd->limiter);
			ft_fileaddback(&(cmd->file),
				ft_newfiles(&token, 3, token->next->state));
		}
		token = token->next;
	}
}

void	fill_redirections_sub(t_prompt *prmpt, t_token *token, t_token *lmt)
{
	while (token && token != lmt)
	{
		if (token->type == REDIR_IN)
			ft_fileaddback(&(prmpt->file),
				ft_newfiles(&token, 0, token->next->state));
		else if (token->type == REDIR_OUT || token->type == APPEND)
			ft_fileaddback(&(prmpt->file),
				ft_newfiles(&token,
					1 + (token->type == APPEND), token->next->state));
		else if (token->type == REDIR_HERE_DOC)
		{
			add_limiters(&prmpt->limiter, token->next, token->next->state);
			join_limit(prmpt->limiter);
			ft_fileaddback(&(prmpt->file),
				ft_newfiles(&token, 3, token->next->state));
		}
		token = token->next;
	}
}
