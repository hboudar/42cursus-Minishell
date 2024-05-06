/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:43:45 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/04 12:12:04 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tokenize_redir_in(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup("<");
	(*token)->size = 1;
	(*token)->type = REDIR_IN;
	(*token)->state = GENERAL;
	*line = *line + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_redir_out(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup(">");
	(*token)->size = 1;
	(*token)->type = REDIR_OUT;
	(*token)->state = GENERAL;
	*line = *line + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_here_doc(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup("<<");
	(*token)->size = 2;
	(*token)->type = REDIR_HERE_DOC;
	(*token)->state = GENERAL;
	*line = *line + 2;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_env(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup("$");
	(*token)->size = 1;
	(*token)->type = ENV;
	(*token)->state = GENERAL;
	*line = *line + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_word(char **line, int *i, t_token **token)
{
	int	j;

	j = 0;
	while ((*line)[j] && (*line)[j] != ' ' && (*line)[j] != '|'
			&& (*line)[j] != '<' && (*line)[j] != '>'
			&& (*line)[j] != '&' && (*line)[j] != ';'
			&& (*line)[j] != '\'' && (*line)[j] != '\"'
			&& (*line)[j] != '(' && (*line)[j] != ')')
		j++;
	(*token)->data = ft_substr(*line, 0, j);
	(*token)->size = j;
	get_token_type(*token);
	(*token)->state = GENERAL;
	*line = *line + j;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}
