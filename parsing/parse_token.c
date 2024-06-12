/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:47:33 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/12 23:43:56 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_error(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == ERROR)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	has_semicolon(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == SEMI_COLON)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	check_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
				i++;
			if (!line[i])
				return (1);
		}
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (!line[i])
				return (1);
		}
		i++;
	}
	return (0);
}

void	fix_token(t_token **token)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	tmp2 = NULL;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->expand)
			tmp->type = ENV;
		if (tmp->type == WHITE_SPACE || (!tmp->data && !tmp->next))
			remove_token(token, tmp);
		else if ((tmp->type == WORD || tmp->type == ENV))
		{
			if (tmp->next && (tmp->next->type == WORD
					|| tmp->next->type == ENV))
				tmp->next->joinable = 1;
		}
		tmp = tmp2;
	}
	expand_wildcard(token);
}

t_token	*parse_token(char *line)
{
	int		i;
	t_token	*tmp;
	t_token	*token;

	i = 0;
	if (check_quotes(line))
	{
		printf("Syntax error\n");
		return (NULL);
	}
	token = (t_token *)malloc(sizeof(t_token));
	ft_bzero(token, sizeof(t_token));
	tmp = token;
	while ((size_t)i < ft_strlen(line))
		tokenize(&line, &i, &tmp);
	if (has_error(token) || has_semicolon(token))
	{
		printf("Syntax error\n");
		free_token(&token);
		return (NULL);
	}
	split_expand(token);
	fix_token(&token);
	set_size(token);
	return (token);
}
