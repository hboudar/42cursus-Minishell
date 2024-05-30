/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:08:22 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/30 21:29:16 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tokenize_whitespace(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup(" ");
	while (ft_is_whitespace((*line)[*i]))
		(*i)++;
	(*token)->size = 1;
	(*token)->type = WHITE_SPACE;
	*line = *line + *i;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	ft_bzero((*token)->next, sizeof(t_token));
	if ((*token)->state == LIMITER)
	{
		(*token)->state = GENERAL;
		(*token)->next->state = LIMITER;
	}
	else
		(*token)->next->state = GENERAL;
	(*token) = (*token)->next;
}

void	tokenize_dquotes(char **line, int *i, t_token **token)
{
	(*i)++;
	if ((*line)[*i] == '\"')
		(*token)->data = ft_strdup("");
	else
	{
		while ((*line)[*i] != '\"')
			(*i)++;
		(*token)->data = ft_substr(*line, 1, *i - 1);
	}
	(*token)->type = WORD;
	(*token)->state = IN_DQUOTES;
	*line = *line + *i + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_squotes(char **line, int *i, t_token **token)
{
	(*i)++;
	if ((*line)[*i] == '\'')
		(*token)->data = ft_strdup("");
	else
	{
		while ((*line)[*i] != '\'')
			(*i)++;
		(*token)->data = ft_substr(*line, 1, *i - 1);
	}
	(*token)->type = WORD;
	(*token)->state = IN_SQUOTES;
	*line = *line + *i + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_pipe(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup("|");
	(*token)->size = 1;
	(*token)->type = PIPE_TKN;
	(*token)->state = GENERAL;
	*line = *line + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_append(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup(">>");
	(*token)->size = 2;
	(*token)->type = APPEND;
	(*token)->state = GENERAL;
	*line = *line + 2;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}
