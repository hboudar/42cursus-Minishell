/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:57:48 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/14 12:09:39 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_limiter(t_limiter **limiter, char *data, int state)
{
	t_limiter	*new;
	t_limiter	*tmp;

	new = (t_limiter *)malloc(sizeof(t_limiter));
	if (!new)
		exit(1);
	new->limit = ft_strdup(data);
	new->quotes = state;
	new->next = NULL;
	if (!*limiter)
	{
		*limiter = new;
		return ;
	}
	tmp = *limiter;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	count_files(char **file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	return (i);
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
			tmp2 = tmp->next;
			remove_token(token, tmp2);
			tmp2 = tmp->next;
			remove_token(token, tmp);
			tmp = tmp2;
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
		{
			ft_fileaddback(&(cmd->file),
				ft_newfile(ft_strdup(token->next->data), 0,
					token->next->state));
			token = token->next;
		}
		else if (token->type == REDIR_OUT || token->type == APPEND)
		{
			ft_fileaddback(&(cmd->file),
				ft_newfile(ft_strdup(token->next->data),
					1 + (token->type == APPEND), token->next->state));
			token = token->next;
		}
		else if (token->type == REDIR_HERE_DOC)
		{
			ft_fileaddback(&(cmd->file), ft_newfile(NULL, 3, token->state));
			add_limiter(&cmd->limiter, token->next->data, token->next->state);
			token = token->next;
		}
		token = token->next;
	}
}

void	fill_redirections_sub(t_prompt *prmpt, t_token *token, t_token *lmt)
{
	while (token && token != lmt)
	{
		if (token->type == REDIR_IN)
		{
			ft_fileaddback(&(prmpt->file),
				ft_newfile(ft_strdup(token->next->data),
					0, token->next->state));
			token = token->next;
		}
		else if (token->type == REDIR_OUT || token->type == APPEND)
		{
			ft_fileaddback(&(prmpt->file),
				ft_newfile(ft_strdup(token->next->data),
					1 + (token->type == APPEND), token->next->state));
			token = token->next;
		}
		else if (token->type == REDIR_HERE_DOC)
		{
			ft_fileaddback(&(prmpt->file), ft_newfile(NULL, 3, token->state));
			add_limiter(&prmpt->limiter, token->next->data, token->next->state);
			token = token->next;
		}
		token = token->next;
	}
}
