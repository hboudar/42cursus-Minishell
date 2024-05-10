/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:17:41 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/10 09:25:15 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == REDIR_IN && (!tmp->next || tmp->next->type != WORD))
			return (1);
		if (tmp->type == REDIR_OUT && (!tmp->next || tmp->next->type != WORD))
			return (1);
		if (tmp->type == APPEND && (!tmp->next || tmp->next->type != WORD))
			return (1);
		if (tmp->type == PIPE_TKN && (!tmp->next
				|| tmp->next->type == PIPE_TKN || tmp->next->type == CLOSEPAR
				|| tmp->next->type == OR_TOKEN || tmp->next->type == AND_TOKEN))
			return (1);
		if (tmp->type == OR_TOKEN && (!tmp->next
				|| tmp->next->type == PIPE_TKN || tmp->next->type == OR_TOKEN
				|| tmp->next->type == AND_TOKEN))
			return (1);
		if (tmp->type == AND_TOKEN && (!tmp->next || tmp->next->type == PIPE_TKN
				|| tmp->next->type == OR_TOKEN || tmp->next->type == AND_TOKEN))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
