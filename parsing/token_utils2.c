/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:31:06 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/06 16:14:06 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_token_limit(t_token **token, t_token *limit)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp && tmp != limit)
	{
		remove_token(token, tmp);
		tmp = *token;
	}
	*token = limit;
}

void	remove_token(t_token **token, t_token *node)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	tmp2 = NULL;
	while (tmp && tmp != node)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (tmp2)
			tmp2->next = tmp->next;
		else
			*token = tmp->next;
		free(tmp->data);
		free(tmp);
	}
}

void	split_token(t_token *token, t_token *split, t_token **res)
{
	t_token	*tmp;
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	ft_bzero(new_token, sizeof(t_token));
	tmp = new_token;
	while (token != split)
	{
		tmp->data = ft_strdup(token->data);
		tmp->expand = ft_dupexpand(token->expand);
		tmp->size = token->size;
		tmp->type = token->type;
		tmp->state = token->state;
		tmp->next = (t_token *)malloc(sizeof(t_token));
		ft_bzero(tmp->next, sizeof(t_token));
		tmp = tmp->next;
		token = token->next;
	}
	end_token(&new_token);
	*res = new_token;
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
	while (tmp->type != PIPE_TKN)
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

void	set_size(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	token->size = i + 1;
	if (token->next)
		set_size(token->next);
}
