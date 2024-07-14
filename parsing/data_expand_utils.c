/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:47:56 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/14 10:08:23 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_args_count(t_data *data)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = data;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	handle_first_arg(t_data **org, char **new_data, t_data **data, int join)
{
	int		i;
	t_data	*tmp;

	i = 0;
	tmp = (t_data *)malloc(sizeof(t_data));
	ft_bzero(tmp, sizeof(t_data));
	tmp->arg = ft_strdup(new_data[0]);
	(*data) = tmp;
	(*data)->joinable = join;
	(*org == NULL) && (*org = *data);
	(new_data[0]) && (i++);
	return (i);
}

void	add_data(t_data **original, t_data **data, char **new_data, int join)
{
	int		i;
	t_data	*tmp;
	t_data	*tmp2;

	i = 0;
	if (!(*data))
		i = handle_first_arg(original, new_data, data, join);
	tmp2 = *data;
	while (new_data[i])
	{
		tmp = (t_data *)malloc(sizeof(t_data));
		ft_bzero(tmp, sizeof(t_data));
		if (i == 0)
			tmp->joinable = join;
		tmp->arg = ft_strdup(new_data[i]);
		tmp->next = tmp2->next;
		tmp2->next = tmp;
		i++;
		tmp2 = tmp;
	}
}

void	addback_data(t_data **data, char *new_data, enum e_state state, int join)
{
	t_data	*tmp;
	t_data	*tmp2;

	tmp = (t_data *)malloc(sizeof(t_data));
	ft_bzero(tmp, sizeof(t_data));
	tmp->arg = ft_strdup(new_data);
	tmp->state = state;
	tmp->joinable = join;
	tmp2 = *data;
	while (tmp2 && tmp2->next)
		tmp2 = tmp2->next;
	if (!tmp2)
		*data = tmp;
	else
		tmp2->next = tmp;
}
