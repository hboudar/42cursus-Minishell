/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:00:31 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/14 12:09:39 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_limiter(t_limiter **limiter)
{
	t_limiter	*tmp;

	while (*limiter)
	{
		tmp = *limiter;
		*limiter = (*limiter)->next;
		if (tmp->limit)
			free(tmp->limit);
		if (tmp)
			free(tmp);
	}
	*limiter = NULL;
}

void	free_data(t_data **data)
{
	t_data	*tmp;

	while (*data)
	{
		tmp = *data;
		*data = (*data)->next;
		if (tmp->arg)
			free(tmp->arg);
		if (tmp)
			free(tmp);
	}
	*data = NULL;
}

void	free_expand(t_expand **expand)
{
	t_expand	*tmp;

	while (*expand)
	{
		tmp = *expand;
		*expand = (*expand)->next;
		if (tmp->data)
			free(tmp->data);
		if (tmp)
			free(tmp);
	}
	*expand = NULL;
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
	if (*cmd)
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
	free_files((*prompt)->file);
	free_limiter(&(*prompt)->limiter);
	if (*prompt)
		free(*prompt);
	*prompt = NULL;
}
