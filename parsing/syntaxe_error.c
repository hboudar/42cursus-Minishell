/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:17:41 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/27 19:24:38 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	was_syntax_error(t_prompt *prompt)
{
	if (prompt->exit_state == 300)
	{
		prompt->exit_state = 258;
		return (1);
	}
	if (prompt->left && was_syntax_error(prompt->left))
		return (1);
	if (prompt->right && was_syntax_error(prompt->right))
		return (1);
	return (0);
}

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
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == OPENPAR || tmp->type == CLOSEPAR)
			i++;
		tmp = tmp->next;
	}
	if (i % 2 != 0)
		return (1);
	tmp = token;
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

int	check_syntax(t_token *tkn)
{
	while (tkn)
	{
		if (tkn->type == REDIR_IN && (!tkn->next || tkn->next->type != WORD))
			return (1);
		if (tkn->type == REDIR_OUT && (!tkn->next || tkn->next->type != WORD))
			return (1);
		if (tkn->type == APPEND && (!tkn->next || tkn->next->type != WORD))
			return (1);
		if (tkn->type == REDIR_HERE_DOC
			&& (!tkn->next || tkn->next->type != WORD))
			return (1);
		if (tkn->type == PIPE_TKN && (!tkn->next
				|| tkn->next->type == PIPE_TKN || tkn->next->type == CLOSEPAR
				|| tkn->next->type == OR_TOKEN || tkn->next->type == AND_TOKEN))
			return (1);
		if (tkn->type == OR_TOKEN && (!tkn->next
				|| tkn->next->type == PIPE_TKN || tkn->next->type == OR_TOKEN
				|| tkn->next->type == AND_TOKEN))
			return (1);
		if (tkn->type == AND_TOKEN && (!tkn->next || tkn->next->type == PIPE_TKN
				|| tkn->next->type == OR_TOKEN || tkn->next->type == AND_TOKEN))
			return (1);
		tkn = tkn->next;
	}
	return (0);
}
