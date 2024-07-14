/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:19:48 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/14 10:10:00 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_last(char ***file, char *data)
{
	int		i;
	char	**new;

	i = 0;
	if (!*file)
	{
		new = (char **)malloc(sizeof(char *) * 2);
		new[0] = ft_strdup(data);
		new[1] = NULL;
		*file = new;
		return ;
	}
	i = count_files(*file);
	new = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*file)[i])
	{
		new[i] = ft_strdup((*file)[i]);
		i++;
	}
	new[i] = ft_strdup(data);
	new[i + 1] = NULL;
	free_tab(file);
	*file = new;
}

t_file	*ft_newfile(t_token *token, int type, enum e_state state)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	ft_bzero(new, sizeof(t_file));
	if (!token->joinable)
	{
		addback_data(&new->args, token->data, token->state, token->joinable);
		new->quotes = state;
	}
	while (token->joinable)
	{
		addback_data(&new->args, token->data, token->state, token->joinable);
		if (type == REDIR_HERE_DOC
			&& (token->state == IN_SQUOTES || token->state == IN_DQUOTES))
			new->quotes = token->state;
		else
			new->quotes = state;
		token = token->next;
	}
	new->type = type;
	return (new);
}

void	ft_fileaddback(t_file **file, t_file *new)
{
	t_file	*tmp;

	if (!*file)
	{
		*file = new;
		return ;
	}
	tmp = *file;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_files(t_file **file)
{
	t_file	*tmp;

	while (*file)
	{
		tmp = *file;
		*file = (*file)->next;
		if (tmp->fd)
			close(tmp->fd);
		if (tmp->data)
		{
			free(tmp->data);
			tmp->data = NULL;
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
	}
}
