/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:25:24 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/11 03:44:03 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tokenize_and(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup("&&");
	(*token)->size = 2;
	(*token)->type = AND_TOKEN;
	(*token)->state = GENERAL;
	*line = *line + 2;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_or(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup("||");
	(*token)->size = 2;
	(*token)->type = OR_TOKEN;
	(*token)->state = GENERAL;
	*line = *line + 2;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_par(char **line, int *i, t_token **token, int type)
{
	if (type == OPENPAR)
	{
		(*token)->data = ft_strdup("(");
		(*token)->size = 1;
		(*token)->type = OPENPAR;
		(*token)->state = GENERAL;
	}
	else
	{
		(*token)->data = ft_strdup(")");
		(*token)->size = 1;
		(*token)->type = CLOSEPAR;
		(*token)->state = GENERAL;
	}
	*line = *line + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize2(char **line, int *i, t_token **token)
{
	if ((*line)[*i] == '<')
	{
		if ((*line)[*i + 1] == '<')
			tokenize_here_doc(line, i, token);
		else
			tokenize_redir_in(line, i, token);
	}
	else if ((*line)[*i] == '$' && (*line)[*i + 1] && (*line)[*i + 1] != '$'
		&& !ft_is_whitespace((*line)[*i + 1]))
		tokenize_env(line, i, token);
	else if ((*line)[*i] == '(')
		tokenize_par(line, i, token, OPENPAR);
	else if ((*line)[*i] == ')')
		tokenize_par(line, i, token, CLOSEPAR);
	else if ((*line)[*i] == ';')
		tokenize_semicolon(line, i, token);
	else if ((*line)[*i] == '&')
		tokenize_error(line, i, token);
	else if ((*line)[*i] == '*')
		tokenize_wildcard(line, i, token);
	else
		tokenize_word(line, i, token);
}

void	tokenize(char **line, int *i, t_token **token)
{
	if (ft_is_whitespace((*line)[*i]))
		tokenize_whitespace(line, i, token);
	else if ((*line)[*i] == '\"')
		tokenize_dquotes(line, i, token);
	else if ((*line)[*i] == '\'')
		tokenize_squotes(line, i, token);
	else if ((*line)[*i] == '|')
	{
		if ((*line)[*i + 1] == '|')
			tokenize_or(line, i, token);
		else
			tokenize_pipe(line, i, token);
	}
	else if ((*line)[*i] == '>')
	{
		if ((*line)[*i + 1] == '>')
			tokenize_append(line, i, token);
		else
			tokenize_redir_out(line, i, token);
	}
	else if ((*line)[*i] == '&' && (*line)[*i + 1] == '&')
		tokenize_and(line, i, token);
	else
		tokenize2(line, i, token);
}
