/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:01:44 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/19 10:58:06 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_env_equal_2(const char *str, t_env *env)
{
	env->next = malloc(sizeof(t_env));
	if (!env->next)
		return (perror("E: malloc in export"));
	env->next->key = ft_substr(str, 0, ft_strchr(str, '=') + 1 - str);
	if (!env->next->key)
		return (free(env->next), perror("E: ft_substr in export"));
	env->next->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!env->next->value)
		return (free(env->next->key),
			free(env->next), perror("E: ft_strdup in export"));
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
			return (perror("E: ft_strdup in export"));
		env->print = PRINT;
		if (ft_strchr(env->key, '='))
			return ;
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (perror("E: ft_strdup in export"));
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
		return (perror("malloc in add_env failed"));
	tmp = ft_substr(str, 0, ft_strchr(str, '+') - str);
	if (!tmp)
		return (free(env->next), perror("ft_strdup in add_env failed"));
	env->next->key = ft_strjoin(tmp, "=");
	free(tmp);
	if (!env->next->key)
		return (free(env->next), perror("ft_strdup in add_env failed"));
	env->next->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!env->next->value)
		return (free(env->next->key), free(env->next),
			perror("ft_strdup in add_env failed"));
	env->next->next = NULL;
	env->print = PRINT;
}

static void	add_env_plus_2(const char *str, t_env *env, char *tmp)
{
	env->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!env->value)
		return (perror("ft_strdup in add_env_plus failed"));
	tmp = env->key;
	env->key = ft_strjoin(env->key, "=");
	free(tmp);
	if (!env->key)
		return (perror("ft_strjoin in add_env_plus failed"));
	env->print = PRINT;
	return ;
}

void	add_env_plus(const char *str, t_env *env, char *tmp, char *tmp2)
{
	tmp = ft_substr(str, 0, ft_strchr(str, '+') - str);
	if (!tmp)
		return (perror("ft_strdup in add_env_plus failed"));
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
			return (perror("ft_strdup in add_env_plus failed"));
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
