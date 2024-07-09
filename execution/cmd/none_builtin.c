/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/23 11:50:34 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_error(char *path)
{
	struct stat	path_stat;

	if (path == NULL || access(path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		if (!path)
			ft_putstr_fd(": command not found\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode) || access(path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		if (S_ISDIR(path_stat.st_mode))
			ft_putstr_fd(":is a directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
}

static void	child_process(t_prompt *prompt, t_env *env, char **envp, char *path)
{
	none_redirection(prompt, env, prompt->cmd->file);
	if (prompt->cmd->args[0] == NULL || strlen(prompt->cmd->args[0]) == 0)
		handle_error(NULL);
	path = find_path(prompt->cmd->args, env);
	handle_error(path);
	envp = env_to_envp(env);
	if (execve(path, prompt->cmd->args, envp) == -1)
		perror("Minishell: execve failed");
	free_envp(envp);
	exit(1);
}

int	none_builtin(t_prompt *prompt, t_env *env, int mode, t_pid **pids)
{
	pid_t	pid;

	if (!mode)
	{
		setup_signal_handlers(sig_handler_child, sig_handler_child);
		pid = fork();
		if (pid == -1)
			perror("fork failed");
		else if (pid == 0)
			child_process(prompt, env, NULL, NULL);
		else
		{
			ignore_signals();
			pid_addback(pids, new_pid(pid));
		}
	}
	else
		child_process(prompt, env, NULL, NULL);
	return (prompt->exit_state);
}
