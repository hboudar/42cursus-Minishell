/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:04:30 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 11:27:08 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_builtin(t_prompt *prompt, t_env **env)
{
	if (!ft_strncmp(prompt->cmd->args[0], "echo", 5))
		prompt->exit_state = (ft_echo(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "cd", 3))
		prompt->exit_state = (ft_cd(prompt, *env, NULL, NULL));
	else if (!ft_strncmp(prompt->cmd->args[0], "pwd", 4))
		prompt->exit_state = (ft_pwd(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "export", 7))
		prompt->exit_state = (ft_export(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "unset", 6))
		prompt->exit_state = (ft_unset(prompt, env));
	else if (!ft_strncmp(prompt->cmd->args[0], "env", 4))
		prompt->exit_state = (ft_env(prompt, *env));
	else
		prompt->exit_state = (ft_exit(prompt));
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
