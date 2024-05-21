/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 08:46:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/20 18:36:54 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin(t_prompt *prompt)
{
	return ((!ft_strncmp(prompt->cmd->args[0], "echo", 5)
			|| !ft_strncmp(prompt->cmd->args[0], "cd", 3)
			|| !ft_strncmp(prompt->cmd->args[0], "pwd", 4)
			|| !ft_strncmp(prompt->cmd->args[0], "export", 7)
			|| !ft_strncmp(prompt->cmd->args[0], "unset", 6)
			|| !ft_strncmp(prompt->cmd->args[0], "env", 4)
			|| !ft_strncmp(prompt->cmd->args[0], "exit", 5)));
}

int	execute_builtin(t_prompt *prompt, t_env **env)
{
	if (!ft_strncmp(prompt->cmd->args[0], "echo", 5))//done
		prompt->exit_state = ft_echo(prompt, *env);
	else if (!ft_strncmp(prompt->cmd->args[0], "cd", 3))//done
		prompt->exit_state = ft_cd(prompt, *env);
	else if (!ft_strncmp(prompt->cmd->args[0], "pwd", 4))//done
		prompt->exit_state = ft_pwd(prompt);
	else if (!ft_strncmp(prompt->cmd->args[0], "export", 7))//done
		prompt->exit_state = ft_export(prompt, *env);
	else if (!ft_strncmp(prompt->cmd->args[0], "unset", 6))//done
		prompt->exit_state = ft_unset(prompt, env);
	else if (!ft_strncmp(prompt->cmd->args[0], "env", 4))//done
		prompt->exit_state = ft_env(prompt, *env);
	else if (!ft_strncmp(prompt->cmd->args[0], "exit", 5))//done
		prompt->exit_state = ft_exit(prompt);
	return (prompt->exit_state);
}
