/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:28:12 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/08 23:39:53 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	check_and_or(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == AND_TOKEN || tmp->type == OR_TOKEN || tmp->type == PIPE_TOKEN)
		{
			if (!tmp->next || tmp->next->type == AND_TOKEN || tmp->next->type == OR_TOKEN)
			{
				printf("syntax error near unexpected token `");
				if (tmp->next->type == AND_TOKEN)
					printf("&&\n");
				else
					printf("||\n");
				return (-1);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
