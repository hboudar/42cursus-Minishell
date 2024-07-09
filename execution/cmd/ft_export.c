/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/19 10:54:00 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_arg(const char *arg, char *equal, char *plus)
{
	int	plus_count;
	int	count;
	int	i;

	(1) && (count = 0, plus_count = 0, i = 0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (arg[++i] && arg[i] != '=')
	{
		if (!plus || (plus && !equal))
		{
			if (!ft_isalnum(arg[i]) && arg[i] != '_')
				return (0);
		}
		else if (plus && equal)
		{
			if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '+')
				return (0);
			(arg[i] == '+') && (plus_count++);
		}
	}
	if (plus && equal && plus < equal && (plus_count != 1 || arg[i - 1] != '+'))
		return (0);
	return (1);
}

static int	check_state(const char *str, t_env *env)
{
	char	*key;
	int		mode;

	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& (env->key[ft_strlen(str)] == '=' || !env->key[ft_strlen(str)]))
		{
			if (env->print == NO_PRINT)
			{
				(env->value) && (free(env->value), env->value = NULL);
				env->print = EXP_PRINT;
				mode = (ft_strchr(env->key, '=') != NULL);
				key = ft_substr(env->key, 0, ft_strlen(env->key) - mode);
				(1) && (free(env->key), env->key = NULL);
				env->key = key;
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static void	add_env(const char *str, t_env *env)
{
	if (check_state(str, env))
		return ;
	while (env->next)
		env = env->next;
	env->next = malloc(sizeof(t_env));
	env->next->key = ft_strdup(str);
	env->next->value = NULL;
	env->next->next = NULL;
	env->next->print = EXP_PRINT;
}

static int	export_only(t_env *env)
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

int	ft_export(t_prompt *prompt, t_env *env, char *equal, char *plus)
{
	int		i;

	if (prompt->cmd->args[1] == NULL)
		return (export_only(env));
	(1) && (i = 0, prompt->exit_state = 0);
	while (prompt->cmd->args[++i])
	{
		equal = ft_strchr(prompt->cmd->args[i], '=');
		plus = ft_strchr(prompt->cmd->args[i], '+');
		if (!check_arg(prompt->cmd->args[i], equal, plus))
		{
			ft_putstr_fd(prompt->cmd->args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			prompt->exit_state = 1;
		}
		else if (check_underscore(prompt->cmd->args[i]))
			;
		else if (!equal && !plus)
			add_env(prompt->cmd->args[i], env);
		else if (!plus || (plus && equal && plus > equal))
			add_env_equal(prompt->cmd->args[i], env);
		else if (plus && equal && plus < equal)
			add_env_plus(prompt->cmd->args[i], env, NULL, NULL);
	}
	return (prompt->exit_state);
}
