/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:47:33 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/30 16:56:12 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	state_type(t_token *tmp)
{
	if (tmp->type == REDIR_IN)
		tmp->next->state = INFILE;
	else if (tmp->type == REDIR_OUT)
		tmp->next->state = OUTFILE;
	else if (tmp->type == ENV)
		tmp->next->state = ENVIROMENT;
	else if (tmp->type == SQUOTES && tmp->state == IN_SQUOTES)
		tmp->next->state = GENERAL;
	else if (tmp->state == IN_DQUOTES)
		tmp->next->state = IN_DQUOTES;
	else if (tmp->state == IN_SQUOTES)
		tmp->next->state = IN_SQUOTES;
	else if (tmp->type == REDIR_HERE_DOC)
		tmp->next->state = LIMITER;
	else
		tmp->next->state = GENERAL;
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
		if (tmp->type == WHITE_SPACE || (!tmp->data && !tmp->next))
			remove_token(token, tmp);
		else if (tmp->type == WORD && tmp->next && tmp->next->type == WORD)
		{
			tmp->data = ft_strjoin(tmp->data, tmp->next->data);
			remove_token(token, tmp->next);
			tmp2 = tmp;
		}
		tmp = tmp2;
	}
}

t_token	*parse_token(char *line, t_env *env)
{
	int		i;
	t_token	*tmp;
	t_token	*token;

	(void)env;
	i = 0;
	if (has_semicolon(line) || check_quotes(line))
	{
		printf("Syntax error\n");
		return (NULL);
	}
	token = (t_token *)malloc(sizeof(t_token));
	ft_bzero(token, sizeof(t_token));
	tmp = token;
	while ((size_t)i < ft_strlen(line))
		tokenize(&line, &i, &tmp);
	split_expand(token);
	expand_tokens(&token, env);
	fix_token(&token);
	set_size(token);
	set_state(token);
	return (token);
}
