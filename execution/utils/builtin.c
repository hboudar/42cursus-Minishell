/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:04:30 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/19 09:32:17 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_builtin(t_prompt *prompt, t_env **env)
{
	if (!ft_strncmp(prompt->cmd->args[0], "echo", 5))
		prompt->exit_state = ft_echo(prompt);
	else if (!ft_strncmp(prompt->cmd->args[0], "cd", 3))
		prompt->exit_state = ft_cd(prompt, *env, NULL, NULL);
	else if (!ft_strncmp(prompt->cmd->args[0], "pwd", 4))
		prompt->exit_state = ft_pwd(*env);
	else if (!ft_strncmp(prompt->cmd->args[0], "export", 7))
		prompt->exit_state = ft_export(prompt, *env, NULL, NULL);
	else if (!ft_strncmp(prompt->cmd->args[0], "unset", 6))
		prompt->exit_state = ft_unset(prompt, env);
	else if (!ft_strncmp(prompt->cmd->args[0], "env", 4))
		prompt->exit_state = ft_env(prompt, *env);
	else
		prompt->exit_state = ft_exit(prompt);
	return (prompt->exit_state);
}

int	is_builtin(t_prompt *prompt)
{
	if (prompt && prompt->cmd && prompt->cmd->args
		&& prompt->cmd->args[0])
		return ((!ft_strncmp(prompt->cmd->args[0], "echo", 5)
				|| !ft_strncmp(prompt->cmd->args[0], "cd", 3)
				|| !ft_strncmp(prompt->cmd->args[0], "pwd", 4)
				|| !ft_strncmp(prompt->cmd->args[0], "export", 7)
				|| !ft_strncmp(prompt->cmd->args[0], "unset", 6)
				|| !ft_strncmp(prompt->cmd->args[0], "env", 4)
				|| !ft_strncmp(prompt->cmd->args[0], "exit", 5)));
	return (0);
}

int	check_underscore(char *arg)
{
	if (!ft_strncmp(arg, "_", 2) || !ft_strncmp(arg, "_=", 2)
		|| !ft_strncmp(arg, "_+", 2))
	{
		free(arg);
		arg = ft_strdup("_");
		return (1);
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
			tmp->print = ENV_PRINT;
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
