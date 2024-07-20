/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:23:09 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 09:23:10 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize_redir_in(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup("<");
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
	(*token)->type = REDIR_HERE_DOC;
	(*token)->state = GENERAL;
	*line = *line + 2;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
	(*token)->state = LIMITER;
}

void	tokenize_env(char **line, int *i, t_token **token)
{
	(*token)->type = ENV;
	if ((*token)->state != LIMITER)
		(*token)->state = GENERAL;
	*line = *line + 1;
	get_expand(line, *token);
	(*token)->data = ft_strjoin("$", *(*token)->expand);
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_word(char **line, int *i, t_token **token)
{
	int	j;

	j = 0;
	if ((*line)[j] == '$' && (*line)[j + 1] == '$')
	{
		while ((*line)[j] == '$')
			j++;
	}
	else
	{
		while (ft_isword((*line)[j])
			|| (((*line)[j] == '$') && !ft_isword((*line)[j + 1])))
			j++;
	}
	(*token)->data = ft_substr(*line, 0, j);
	(*token)->type = WORD;
	*line = *line + j;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}
