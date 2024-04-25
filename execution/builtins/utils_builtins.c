/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 08:46:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/25 16:50:11 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

int	execute_builtin(t_prompt *prompt)
{
	if (!ft_strncmp(prompt->cmd->args[0], "echo", 5))
		return (ft_echo(prompt));
	else if (!ft_strncmp(prompt->cmd->args[0], "cd", 3))
		return (ft_cd(prompt));
	else if (!ft_strncmp(prompt->cmd->args[0], "pwd", 4))
		return (ft_pwd(prompt));
	else if (!ft_strncmp(prompt->cmd->args[0], "export", 7))
		return (ft_export(prompt));
	else if (!ft_strncmp(prompt->cmd->args[0], "unset", 6))
		return (ft_unset(prompt));
	else if (!ft_strncmp(prompt->cmd->args[0], "env", 4))
		return (ft_env(prompt));
	else if (!ft_strncmp(prompt->cmd->args[0], "exit", 5))
		return (ft_exit(prompt));
}
