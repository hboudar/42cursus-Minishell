/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:48:37 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/19 17:58:41 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_type_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strchr(tmp->key, '=') && ft_strncmp(tmp->key, "_=", 3))
			tmp->print = PRINT;
		else if (!ft_strncmp(tmp->key, "_=", 3))
			tmp->print = ENV_PRINT;
		else
			tmp->print = EXP_PRINT;
		tmp = tmp->next;
	}
}

t_env	*ft_tabdup(char **args, int i, int j)
{
	t_env	*tmp;
	t_env	*newenv;

	newenv = (t_env *)malloc(sizeof(t_env));
	if (!newenv)
		exit(1);
	tmp = newenv;
	while (args[++i])
	{
		j = 0;
		if (!ft_strncmp(args[i], "OLDPWD", 6))
			continue ;
		while (args[i][j] && args[i][j] != '=')
			j++;
		tmp->key = ft_substr(args[i], 0, j + 1);
		tmp->value = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j - 1);
		tmp->next = (t_env *)malloc(sizeof(t_env));
		ft_bzero(tmp->next, sizeof(t_env));
		tmp = tmp->next;
	}
	tmp->key = ft_strdup("OLDPWD");
	set_type_env(newenv);
	ft_shell_lvl(newenv);
	return (newenv);
}

int	check_env(char **envp)
{
	if (envp && !envp[0])
	{
		printf("Error: empty enviroment\n");
		return (1);
	}
	return (0);
}

void	ft_shell_lvl(t_env *env)
{
	char	*str;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 5))
		{
			str = ft_itoa(ft_atoi(tmp->value) + 1);
			if (!str)
				return (ft_putstr_fd("E: ft_itoa in ft_shell_lvl"));
			if (ft_strncmp(tmp->value, "999", 3) == 0)
			{
				free(str);
				free(tmp->value);
				return ;
			}
			free(tmp->value);
			tmp->value = str;
			break ;
		}
		tmp = tmp->next;
	}
}
