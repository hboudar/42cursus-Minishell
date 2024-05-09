/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:17:41 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/09 16:47:03 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_syntax(t_token *token)
{
	t_token	*tmp;

    tmp = token;
    while (tmp->next)
    {
        if (tmp->type == REDIR_IN && tmp->next->type != WORD)
            return (1);
        if (tmp->type == REDIR_OUT && tmp->next->type != WORD)
            return (1);
        if (tmp->type == APPEND && tmp->next->type != WORD)
            return (1);
        if (tmp->type == PIPE_TOKEN && (tmp->next->type == PIPE_TOKEN || tmp->next->type == CLOSEPAR
            || tmp->next->type == OR_TOKEN || tmp->next->type == AND_TOKEN))
            return (1);
        if (tmp->type == OR_TOKEN && (tmp->next->type == PIPE_TOKEN 
            || tmp->next->type == OR_TOKEN || tmp->next->type == AND_TOKEN))
            return (1);
        if (tmp->type == AND_TOKEN && (tmp->next->type == PIPE_TOKEN
            || tmp->next->type == OR_TOKEN || tmp->next->type == AND_TOKEN))
            return (1);
        tmp = tmp->next;
    }
    return (0);
}
