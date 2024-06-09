/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:00:31 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/09 19:56:06 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_limiter(t_limiter **limiter)
{
	t_limiter	*tmp;

	while (*limiter)
	{
		tmp = *limiter;
		*limiter = (*limiter)->next;
		free(tmp->limit);
		free(tmp);
	}
}

void	free_data(t_data **data)
{
	t_data	*tmp;

	while (*data)
	{
		tmp = *data;
		*data = (*data)->next;
		free(tmp->arg);
		free(tmp);
	}
}

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
	free_limiter(&(*cmd)->limiter);
	free_files((*cmd)->file);
	free_expand(&(*cmd)->expand);
	free_data(&(*cmd)->data);
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
