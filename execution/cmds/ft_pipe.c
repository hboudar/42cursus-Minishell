/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:16:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/18 12:25:30 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	do_left(t_prompt *prompt, t_env **env, int *fd, t_pid **pids)
{
	pid_t	pid;

	setup_signal_handlers(sig_handler_child, sig_handler_child);
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		(1) && (dup2(fd[1], 1), close(fd[0]), close(fd[1]));
		if (is_builtin(prompt))
			exit(ft_builtin(prompt, env));
		else
			none_builtin(prompt, *env, 1, pids);
	}
	else
	{
		ignore_signals();
		pid_addback(pids, new_pid(pid));
		(1) && (dup2(fd[0], 0), close(fd[0]), close(fd[1]));
	}
}

int	do_right(t_prompt *prompt, t_env **env, t_pid **pids)
{
	pid_t	pid;

	setup_signal_handlers(sig_handler_child, sig_handler_child);
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		if (is_builtin(prompt))
		{
			redirection(prompt, env, prompt->cmd->file);
			exit(prompt->exit_state);
		}
		else
			none_builtin(prompt, *env, 1, pids);
	}
	else
	{
		ignore_signals();
		pid_addback(pids, new_pid(pid));
	}
	return (prompt->exit_state);
}

int	ft_pipe(t_prompt *prompt, t_env **env, char side, t_pid **pids)
{
	int	fd[2];

	if (side == 'L')
		if (pipe(fd) == -1)
			error("pipe");
	if (prompt->subshell)
	{
		(side == 'L') && (prompt->exit_state = subshell(prompt, env, fd, pids));
		(side == 'R')
			&& (prompt->exit_state = subshell(prompt, env, NULL, pids));
	}
	else if (prompt->type == P_CMD)
	{
		expand_cmd(prompt, *env);
		(side == 'L') && (do_left(prompt, env, fd, pids), side = 'L');
		(side == 'R') && (do_right(prompt, env, pids), side = 'R');
	}
	else
		prompt->exit_state = execution(prompt, env, pids);
	return (prompt->exit_state);
}
