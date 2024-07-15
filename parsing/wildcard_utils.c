/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:39:36 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/15 20:55:17 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_files_data(t_data **data, t_data *limit, char **files, int *len)
{
    int		i;
    t_data	*tmp;
    t_data	*new;

    tmp = *data;
    i = 1;
    while (tmp && tmp->next != limit)
        tmp = tmp->next;
    free(tmp->arg);
    tmp->arg = ft_strdup(files[0]);
    while (files[i])
    {
        new = (t_data *)malloc(sizeof(t_data));
        if (!new)
        {
            perror("malloc");
            exit(1);
        }
        ft_bzero(new, sizeof(t_data));
        new->arg = ft_strdup(files[i]);
        new->next = tmp->next;
        tmp->next = new;
        tmp = tmp->next;
        i++;
    }
    *len += i - 1;
}
