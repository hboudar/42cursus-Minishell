/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:17:41 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/07 22:18:31 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_syntax(t_token *token)
{
	t_token	*tmp;

    tmp = token;
    while (tmp->next)
    {
        if (tmp->type == P_CMD && tmp->next->type == P_CMD)
            return (1);
        if (tmp->type == P_PIPE && tmp->next->type == P_PIPE)
            return (1);
        if (tmp->type == P_AND && tmp->next->type == P_AND)
            return (1);
        if (tmp->type == P_OR && tmp->next->type == P_OR)
            return (1);
        if (tmp->type == P_PIPE && tmp->next->type == P_AND)
            return (1);
        if (tmp->type == P_PIPE && tmp->next->type == P_OR)
            return (1);
        if (tmp->type == P_AND && tmp->next->type == P_PIPE)
            return (1);
        if (tmp->type == P_AND && tmp->next->type == P_OR)
            return (1);
        if (tmp->type == P_OR && tmp->next->type == P_PIPE)
            return (1);
        if (tmp->type == P_OR && tmp->next->type == P_AND)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}
