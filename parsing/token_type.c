/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:08:22 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/19 20:02:11 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tokenize_whitespace(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup(" ");
	while ((*line)[*i] == ' ')
		(*i)++;
	(*token)->size = 1;
	(*token)->type = WHITE_SPACE;
	(*token)->state = GENERAL;
	*line = *line + *i;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
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
	get_token_type(*token);
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
	get_token_type(*token);
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
