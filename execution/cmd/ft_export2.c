/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:55:07 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/19 17:57:53 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_env_equal_2(const char *str, t_env *env)
{
	env->next = malloc(sizeof(t_env));
	if (!env->next)
		return (ft_putstr_fd("E: malloc in export\n", 2));
	env->next->key = ft_substr(str, 0, ft_strchr(str, '=') + 1 - str);
	if (!env->next->key)
		return (free(env->next), ft_putstr_fd("E: ft_substr in export\n", 2));
	env->next->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!env->next->value)
		return (free(env->next->key),
			free(env->next), ft_putstr_fd("E: ft_strdup in export\n", 2));
	env->next->next = NULL;
	env->next->print = PRINT;
}

void	add_env_equal(const char *str, t_env *env)
{
	char	*tmp;

	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(env->key)) || !env->next)
			break ;
		env = env->next;
	}
	if (!ft_strncmp(env->key, str, ft_strlen(env->key)))
	{
		(env->value) && (free(env->value), env->value = NULL);
		env->value = ft_strdup(ft_strchr(str, '=') + 1);
		if (!env->value)
			return (ft_putstr_fd("E: ft_strdup in export\n", 2));
		env->print = PRINT;
		if (ft_strchr(env->key, '='))
			return ;
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (ft_putstr_fd("E: ft_strdup in export\n", 2));
		free(env->key);
		env->key = tmp;
	}
	else
		add_env_equal_2(str, env);
}

static void	add_env_plus_3(const char *str, t_env *env, char *tmp)
{
	env->next = malloc(sizeof(t_env));
	if (!env->next)
		return (ft_putstr_fd("malloc in add_env failed\n", 2));
	tmp = ft_substr(str, 0, ft_strchr(str, '+') - str);
	if (!tmp)
	{
		free(env->next);
		env->next = NULL;
		return (ft_putstr_fd("ft_strdup in add_env failed\n", 2));
	}
	env->next->key = ft_strjoin(tmp, "=");
	free(tmp);
	if (!env->next->key)
	{
		free(env->next);
		env->next = NULL;
		return (ft_putstr_fd("ft_strdup in add_env failed\n", 2));
	}
	env->next->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!env->next->value)
		return (free(env->next->key), free(env->next),
			ft_putstr_fd("ft_strdup in add_env failed\n", 2));
	env->next->next = NULL;
	env->print = PRINT;
}

static void	add_env_plus_2(const char *str, t_env *env, char *tmp)
{
	env->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!env->value)
		return (ft_putstr_fd("ft_strdup in add_env_plus failed\n", 2));
	tmp = env->key;
	env->key = ft_strjoin(env->key, "=");
	free(tmp);
	if (!env->key)
		return (ft_putstr_fd("ft_strjoin in add_env_plus failed\n", 2));
	env->print = PRINT;
	return ;
}

void	add_env_plus(const char *str, t_env *env, char *tmp, char *tmp2)
{
	tmp = ft_substr(str, 0, ft_strchr(str, '+') - str);
	if (!tmp)
		return (ft_putstr_fd("ft_strdup in add_env_plus failed\n", 2));
	while (env)
	{
		if (!ft_strncmp(env->key, tmp, ft_strlen(tmp)) || !env->next)
			break ;
		env = env->next;
	}
	if (!ft_strncmp(env->key, tmp, ft_strlen(tmp)) && ft_strchr(env->key, '='))
	{
		(env->print == NO_PRINT) && (free(env->value), env->value = NULL);
		(env->print != NO_PRINT) && (free(tmp), tmp = env->value);
		tmp2 = ft_strjoin(env->value, ft_strchr(str, '=') + 1);
		if (!tmp2)
			return (ft_putstr_fd("ft_strdup in add_env_plus failed\n", 2));
		env->value = tmp2;
		env->print = PRINT;
	}
	else if (!ft_strncmp(env->key, tmp, ft_strlen(tmp))
		&& !ft_strchr(env->key, '='))
		add_env_plus_2(str, env, NULL);
	else
		add_env_plus_3(str, env, NULL);
	free(tmp);
}
