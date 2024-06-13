/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:04:30 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/13 02:17:41 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int	ft_builtin(t_prompt *prompt, t_env **env)
{
	if (!ft_strncmp(prompt->cmd->args[0], "echo", 5))//done
		return (ft_echo(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "cd", 3))//done
		return (ft_cd(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "pwd", 4))//done
		return (ft_pwd(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "export", 7))//done
		return (ft_export(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "unset", 6))//done
		return (ft_unset(prompt, env));
	else if (!ft_strncmp(prompt->cmd->args[0], "env", 4))//done
		return (ft_env(prompt, *env));
	return (ft_exit(prompt));
}

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
