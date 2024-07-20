/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:07:44 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/20 15:23:14 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_pid(t_pid **pid)
{
	t_pid	*tmp;

	while (*pid)
	{
		tmp = (*pid)->next;
		free(*pid);
		*pid = tmp;
	}
	*pid = NULL;
}

t_pid	*new_pid(pid_t pid)
{
	t_pid	*new;

	new = (t_pid *)malloc(sizeof(t_pid));
	if (!new)
	{
		ft_putstr_fd("malloc\n", 2);
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
