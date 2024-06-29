/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:14 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/19 09:17:39 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_prompt *prompt, t_env *env)
{
	char	*path;

	if (prompt->cmd->args[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	path = find_path(prompt->cmd->args, env);
	if (!path || !ft_strncmp(path, "env", 4))
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	free (path);
	while (env)
	{
		if (env->value && (env->print == ENV_PRINT || env->print == PRINT))
			printf("%s%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	export_only(t_env *env)
{
	while (env)
	{
		if (env->print == PRINT || env->print == EXP_PRINT)
		{
			if (env->value)
				printf("declare -x %s\"%s\"\n", env->key, env->value);
			else
				printf("declare -x %s\n", env->key);
		}
		env = env->next;
	}
	return (0);
}

int	change_underscore(t_env **env, char *str)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "_=", 3))
		{
			(tmp->value) && (free(tmp->value), tmp->value = NULL);
			tmp->value = ft_strdup(str);
			if (!tmp->value)
				return (1);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}
