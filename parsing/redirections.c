/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:57:48 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/14 21:52:08 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fill_redirections(t_cmd *cmd, t_token *token)
{
	while (token)
	{
		if (token->type == REDIR_IN)
			ft_infileaddback(&(cmd->infile),
				ft_newinfile(ft_strdup(token->next->data)));
		else if (token->type == REDIR_OUT || token->type == APPEND)
		{
			ft_outfileaddback(&(cmd->outfile),
				ft_newoutfile(ft_strdup(token->next->data)));
			cmd->outfile->appendable = token->type == APPEND;
        }
		else if (token->type == HERE_DOC)
			cmd->limiter = add_last(cmd->limiter, ft_strdup(token->next->data));
		token = token->next;
	}
}
