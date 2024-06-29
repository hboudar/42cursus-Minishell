/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:07:32 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/14 12:09:39 by aoulahra         ###   ########.fr       */
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

t_file	*ft_newfile(char *data, int type, enum e_state state)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	new->data = data;
	new->type = type;
	new->quotes = state;
	new->next = NULL;
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

void	free_files(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file;
		file = file->next;
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
