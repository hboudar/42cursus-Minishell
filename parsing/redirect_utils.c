/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:07:32 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/01 17:56:03 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

t_file	*ft_newfile(char *data, int type)
{
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	new->data = data;
	new->type = type;
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
		free(tmp->data);
		free(tmp);
	}
}
