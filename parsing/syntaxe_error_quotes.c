/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:41:31 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/29 15:47:44 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_quote(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SQUOTES)
		{
			while (tmp->next && tmp->next->type != SQUOTES)
				tmp = tmp->next;
			if (!tmp->next)
				return (1);
		}
		if (tmp->type == DQUOTES)
		{
			while (tmp->next && tmp->next->type != DQUOTES)
				tmp = tmp->next;
			if (!tmp->next)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
