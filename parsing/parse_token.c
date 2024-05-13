/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:47:33 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/13 14:50:43 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	set_state(t_token	*token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
	{
		state_type(tmp);
		tmp = tmp->next;
	}
}

void	set_size(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	token->size = i + 1;
	if (token->next)
		set_size(token->next);
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
		if (tmp->type == WHITE_SPACE || !tmp->data)
			remove_token(token, tmp);
		tmp = tmp2;
	}
}

t_token	*parse_token(char *line)
{
	int		i;
	t_token	*tmp;
	t_token	*token;

	i = 0;
	token = (t_token *)malloc(sizeof(t_token));
	ft_bzero(token, sizeof(t_token));
	tmp = token;
	while ((size_t)i < ft_strlen(line))
		tokenize(&line, &i, &tmp);
	tmp->next = NULL;
	set_size(token);
	set_state(token);
	return (token);
}
