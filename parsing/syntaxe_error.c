/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:17:41 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/14 20:01:02 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_semicolon(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';')
			return (1);
		i++;
	}
	return (0);
}

int	check_syntax_bonus(t_token *token)
{
	while (token)
	{
		if (token->type == OPENPAR && (!token->next
				|| token->next->type == PIPE_TKN
				|| token->next->type == OR_TOKEN
				|| token->next->type == AND_TOKEN
				|| token->next->type == CLOSEPAR))
			return (1);
		token = token->next;
	}
	return (0);
}

int	check_syntax(t_token *token)
{
	while (token)
	{
		if (token->type == REDIR_IN && (!token->next || token->next->type != WORD))
			return (1);
		if (token->type == REDIR_OUT && (!token->next || token->next->type != WORD))
			return (1);
		if (token->type == APPEND && (!token->next || token->next->type != WORD))
			return (1);
		if (token->type == PIPE_TKN && (!token->next
				|| token->next->type == PIPE_TKN || token->next->type == CLOSEPAR
				|| token->next->type == OR_TOKEN || token->next->type == AND_TOKEN))
			return (1);
		if (token->type == OR_TOKEN && (!token->next
				|| token->next->type == PIPE_TKN || token->next->type == OR_TOKEN
				|| token->next->type == AND_TOKEN))
			return (1);
		if (token->type == AND_TOKEN && (!token->next || token->next->type == PIPE_TKN
				|| token->next->type == OR_TOKEN || token->next->type == AND_TOKEN))
			return (1);
		token = token->next;
	}
	return (0);
}
