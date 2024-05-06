/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:24:03 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/06 16:50:38 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_tablen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	free_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_null_end(t_env **new_args, int i)
{
	int		j;
	t_env	*tmp;

	j = 0;
	tmp = *new_args;
	while (j < i - 1)
	{
		tmp = tmp->next;
		j++;
	}
	free(tmp->next);
	tmp->next = NULL;
}

t_env	*ft_tabdup(char **args)
{
	int		i;
	int		j;
	t_env	*new_args;
	t_env	*tmp;

	i = 0;
	new_args = (t_env *)malloc(sizeof(t_env));
	tmp = new_args;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		tmp->key = ft_substr(args[i], 0, j);
		tmp->value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp = tmp->next;
		i++;
	}
	ft_null_end(&new_args, i);
	return (new_args);
}

int	ft_iswhitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > 13 || str[i] < 9) && str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}
