/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 12:11:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	child_process(t_prompt *prompt, t_env *env)
{
	char	**envp;
	char	*path;

	non_redirection(prompt, env, prompt->cmd->file);
	if (!prompt->cmd->args)
		path = NULL;
	else if (ft_strchr(prompt->cmd->args[0], '/'))
		path = prompt->cmd->args[0];
	else
		path = find_path(prompt->cmd->args, env);
	if ((path && access(path, F_OK) == -1)
		|| ((prompt->cmd->args && !prompt->cmd->args[0][0])))
	{
		printf("minishell: %s: command not found\n", prompt->cmd->args[0]);
		exit(127);
	}
	if (path && access(path, X_OK) == -1)
	{
		printf("minishell: %s: permission denied\n", prompt->cmd->args[0]);
		exit(126);
	}
	(1) && (envp = env_to_envp(env, env), execve(path, prompt->cmd->args, envp));
	if (prompt->cmd->args)
		perror(prompt->cmd->args[0]);
	exit(127);
}

int	exec_nonebuiltin(t_prompt *prompt, t_env *env, int mode, t_pid **pids)
{
	pid_t	pid;

	if (!mode)
	{
		setup_signal_handlers(sig_handler_child, sig_handler_child);
		pid = fork();
		if (pid == -1)
			return (error("fork failed"));
		else if (pid == 0)
			child_process(prompt, env);
		else
		{
			ignore_signals();
			pid_addback(pids, new_pid(pid));
		}
	}
	else
		child_process(prompt, env);
	return (prompt->exit_state);
}
