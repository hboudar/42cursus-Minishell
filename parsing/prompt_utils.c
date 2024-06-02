/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:28:12 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/01 16:45:02 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_expand(t_expand **expand)
{
	t_expand	*tmp;

	while (*expand)
	{
		tmp = *expand;
		*expand = (*expand)->next;
		free(tmp->data);
		free(tmp);
	}
}

void	free_cmd(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (!*cmd)
		return ;
	free_tab(&(*cmd)->args);
	free_tab(&(*cmd)->limiter);
	free_files((*cmd)->file);
	free_expand(&(*cmd)->expand);
	(*cmd)->expand = NULL;
	(*cmd)->args = NULL;
	(*cmd)->limiter = NULL;
	(*cmd)->file = NULL;
	free(*cmd);
	*cmd = NULL;
}

void	free_prompt(t_prompt **prompt)
{
	if (!*prompt)
		return ;
	free_prompt(&(*prompt)->left);
	free_prompt(&(*prompt)->right);
	free_cmd(&(*prompt)->cmd);
	free(*prompt);
	*prompt = NULL;
}

t_token	*get_and_or(t_token *token)
{
	while (token)
	{
		if (token->type == AND_TOKEN || token->type == OR_TOKEN)
			return (token);
		token = token->next;
	}
	return (NULL);
}

int	check_and_or(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == AND_TOKEN || tmp->type == OR_TOKEN)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
