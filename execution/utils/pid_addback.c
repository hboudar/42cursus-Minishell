/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 04:14:06 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/14 04:24:26 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_pid    *new_pid(pid_t pid)
{
    t_pid	*new;

    new = (t_pid *)malloc(sizeof(t_pid));
    if (!new)
    {
        perror("malloc");
        return (NULL);
    }
    new->pid = pid;
    new->next = NULL;
    return (new);
}

void	pid_addback(t_pid **pid, t_pid *new)
{
    t_pid	*tmp;

    if (!*pid)
    {
        *pid = new;
        return ;
    }
    tmp = *pid;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
