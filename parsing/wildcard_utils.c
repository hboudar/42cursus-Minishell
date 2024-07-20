/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:39:36 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/20 13:43:27 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_wildcard_file(t_file *file)
{
	int		len;
	char	**files;

	files = NULL;
	if (ft_strchr(file->data, '*'))
		files = get_files(file->data);
	len = ft_tablen(files);
	if (len == 1 && !file->args->state)
	{
		free(file->data);
		file->data = ft_strdup(files[0]);
	}
	else if (len > 1 && !file->args->state)
	{
		free(file->data);
		file->data = ft_strdup("");
	}
	free_tab(&files);
}

void	add_files_data(t_data **data, t_data *limit, char **files, int *len)
{
	int		i;
	t_data	*tmp;
	t_data	*new;

	tmp = *data;
	i = 0;
	while (tmp && tmp->next != limit)
		tmp = tmp->next;
	free(tmp->arg);
	tmp->arg = ft_strdup(files[0]);
	while (files[++i])
	{
		new = (t_data *)malloc(sizeof(t_data));
		if (!new)
		{
			ft_putstr_fd("malloc\n", 2);
			exit(1);
		}
		ft_bzero(new, sizeof(t_data));
		new->arg = ft_strdup(files[i]);
		new->next = tmp->next;
		tmp->next = new;
		tmp = tmp->next;
	}
	*len += i - 1;
}
