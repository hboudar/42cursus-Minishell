/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:25:24 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/01 16:21:33 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    tokenize2(char **line, int *i, t_token **token)
{
    if ((*line)[*i] == '<')
	{
		if ((*line)[*i + 1] == '<')
			tokenize_here_doc(line, i, token);
		else
			tokenize_redir_in(line, i, token);
	}
	else if ((*line)[*i] == '$')
		tokenize_env(line, i, token);
	else
		tokenize_word(line, i, token);
}

void    tokenize(char **line, int *i, t_token **token)
{
	if ((*line)[*i] == ' ')
	    tokenize_whitespace(line, i, token);
	else if ((*line)[*i] == '\"')
		tokenize_dquotes(line, i, token);
	else if ((*line)[*i] == '\'')
		tokenize_squotes(line, i, token);
	else if ((*line)[*i] == '|')
		tokenize_pipe(line, i, token);
	else if ((*line)[*i] == '>')
	{
		if ((*line)[*i + 1] == '>')
			tokenize_append(line, i, token);
		else
			tokenize_redir_out(line, i, token);
	}
    else
        tokenize2(line, i, token);
}
