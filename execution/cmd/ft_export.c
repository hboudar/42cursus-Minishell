/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 11:27:08 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_key(const char *name)
{
	char	*tmp;

	tmp = (char *)name;
	while (*tmp && *tmp != '=')
	{
		if (ft_is_whitespace(*tmp))
			return (0);
		tmp++;
	}
	if (!*tmp)
		return (0);
	return (1);
}

static int	is_valid(const char *name, int i, int mode)
{
	char	*equal;
	char	*plus;

	if (!mode)
	{
		if (!ft_isalpha(name[0]) && name[0] != '_')
			return (0);
		else if (check_key(name))
			return (1);
		while (name[i])
		{
			if (!ft_isalnum(name[i]) && name[i] != '_')
				return (0);
			i++;
		}
		return (1);
	}
	(1) && (equal = ft_strchr(name, '='), plus = ft_strchr(name, '+'));
	if (!equal && !plus)
		return (0);
	else if (!plus || (plus && equal && plus > equal))
		return (1);
	else if (plus && equal && plus < equal)
		return (2);
	return (1);
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

static void	add_env(const char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key, str, ft_strlen(str))
			&& (env->key[ft_strlen(str)] == '='
				|| env->key[ft_strlen(str)] == '\0'))
			return ;
		if (!env->next)
			break ;
		env = env->next;
	}
	env->next = malloc(sizeof(t_env));
	if (!env->next)
	{
		perror("malloc in add_env failed");
		return ;
	}
	env->next->key = ft_strdup(str);
	if (!env->next->key)
	{
		free(env->next);
		perror("ft_strdup in add_env failed");
		return ;
	}
	(1) && (env->next->value = NULL, env->next->next = NULL,
		env->next->print = EXP_PRINT);
}

int	ft_export(t_prompt *prompt, t_env *env)
{
	int	i;

	if (prompt->cmd->args[1] == NULL)
		return (export_only(env));
	i = 0;
	while (prompt->cmd->args[++i])
	{
		if (!is_valid(prompt->cmd->args[i], 1, 0))
		{
			printf("export: `%s': not a valid identifier\n",
				prompt->cmd->args[i]);
			prompt->exit_state = 1;
		}
		else if (!is_valid(prompt->cmd->args[i], 1, 1))
			add_env(prompt->cmd->args[i], env);
		else if (is_valid(prompt->cmd->args[i], 1, 1) == 1)
			add_env_equal(prompt->cmd->args[i], env);
		else if (is_valid(prompt->cmd->args[i], 1, 1) == 2)
			add_env_plus(prompt->cmd->args[i], env);
	}
	return (0);
}
