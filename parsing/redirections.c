/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:57:48 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/26 16:14:07 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APPEND || tmp->type == REDIR_HERE_DOC)
		{
			remove_token(token, tmp->next);
			remove_token(token, tmp);
			tmp = *token;
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
				ft_newfile(ft_strdup(token->next->data), 0));
			token = token->next;
		}
		else if (token->type == REDIR_OUT || token->type == APPEND)
		{
			ft_fileaddback(&(cmd->file),
				ft_newfile(ft_strdup(token->next->data),
					1 + (token->type == APPEND)));
			token = token->next;
		}
		else if (token->type == REDIR_HERE_DOC)
		{
			ft_fileaddback(&(cmd->file), ft_newfile(NULL, 3));
			add_last(&cmd->limiter, ft_strdup(token->next->data));
			token = token->next;
		}
		token = token->next;
	}
}
