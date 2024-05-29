/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:17:41 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/29 14:53:45 by aoulahra         ###   ########.fr       */
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

int	check_par(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == OPENPAR)
		{
			tmp = get_closepar(tmp);
			if (!tmp || (tmp->next && (tmp->next->type == WORD || tmp->next->type == OPENPAR))
				|| (tmp->next && tmp->next->type == WHITE_SPACE && tmp->next->next
					&& (tmp->next->next->type == WORD || tmp->next->next->type == OPENPAR)))
				return (1);
		}
		tmp = tmp->next;
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
	while (tmp)
	{
		if (tmp->type == OPENPAR && (!tmp->next
				|| tmp->next->type == PIPE_TKN
				|| tmp->next->type == OR_TOKEN
				|| tmp->next->type == AND_TOKEN
				|| tmp->next->type == CLOSEPAR))
			return (1);
		tmp = tmp->next;
	}
	return (check_par(token));
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
