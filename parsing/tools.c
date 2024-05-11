/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:24:03 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/10 23:44:04 by aoulahra         ###   ########.fr       */
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

void	set_type_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strchr(tmp->key, '='))
			tmp->print = ENV_PRINT;
		else
			tmp->print = EXP_PRINT;
		tmp = tmp->next;
	}
}

t_env	*ft_tabdup(char **args)
{
	int		i;
	int		j;
	t_env	*new_args;
	t_env	*tmp;

	i = -1;
	new_args = (t_env *)malloc(sizeof(t_env));
	tmp = new_args;
	if (!args)
		return (empty_env());
	while (args[++i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '=')
			j++;
		tmp->key = ft_substr(args[i], 0, j + 1);
		tmp->value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
		tmp->next = (t_env *)malloc(sizeof(t_env));
		tmp = tmp->next;
	}
	tmp->key = ft_strdup("OLDPWD");
	tmp->value = NULL;
	tmp->next = NULL;
	set_type_env(new_args);
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
