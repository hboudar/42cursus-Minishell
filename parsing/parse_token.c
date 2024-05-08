/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:47:33 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/07 22:46:52 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_type(t_token *tmp)
{
	if (tmp->type == INFILE)
		tmp->next->state = INFILE;
	else if (tmp->type == OUTFILE)
		tmp->next->state = OUTFILE;
	else if (tmp->type == ENVIROMENT)
		tmp->next->state = ENVIROMENT;
	else if (tmp->type == GENERAL)
		tmp->next->state = GENERAL;
	else if (tmp->type == SQUOTES && tmp->state == IN_SQUOTES)
		tmp->next->state = GENERAL;
	else if (tmp->state == DQUOTES)
		tmp->next->state = IN_DQUOTES;
	else if (tmp->state == SQUOTES)
		tmp->next->state = IN_SQUOTES;
	else if (tmp->type == HERE_DOC)
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

t_token	*pipeless_token(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp_new;
	t_token	*new_token;
	int		i;

	i = 0;
	tmp = token;
	new_token = (t_token *)malloc(sizeof(t_token));
	tmp_new = new_token;
	while (tmp->type != PIPE_TOKEN)
	{
		tmp_new->data = ft_strdup(tmp->data);
		tmp_new->type = tmp->type;
		tmp_new->state = tmp->state;
		tmp_new->next = (t_token *)malloc(sizeof(t_token));
		tmp_new = tmp_new->next;
		tmp = tmp->next;
		i++;
	}
	new_token->size = i;
	return (new_token);
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
		if (tmp->type == WHITE_SPACE)
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
	if (!check_syntax(token))
	{
		printf("syntax error\n");
		free_token(token);
		return (NULL);
	}
	fix_token(&token);
	set_size(token);
	set_state(token);
	return (token);
}
