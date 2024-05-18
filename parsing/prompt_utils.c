/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:28:12 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/17 18:54:00 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_prompt(t_prompt **prompt)
{
	if (!*prompt)
		return ;
	free_prompt(&(*prompt)->left);
	free_prompt(&(*prompt)->right);
	free_cmd(&(*prompt)->cmd);
	free(*prompt);
	*prompt = NULL;
}

t_token	*get_and_or_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == AND_TOKEN || token->type == OR_TOKEN || token->type == PIPE_TKN)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int	check_and_or_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == AND_TOKEN || tmp->type == OR_TOKEN || tmp->type == PIPE_TKN)
		{
			if (!tmp->next || tmp->next->type == AND_TOKEN
				|| tmp->next->type == OR_TOKEN || tmp->next->type == PIPE_TKN)
			{
				printf("syntax error near unexpected token `");
				if (tmp->next->type == AND_TOKEN)
					printf("&&\n");
				else if (tmp->next->type == OR_TOKEN)
					printf("||\n");
				else
					printf("|\n");
				return (-1);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
