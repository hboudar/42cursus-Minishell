/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:35:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 05:35:56 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	subshell(t_prompt *prompt, t_env **env, int *fd, t_pid **pids)
{
	extern int	g_caught;
	pid_t	pid;

	prompt->subshell = 0;
	ignore_signals();
	g_caught = 0;
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		setup_signal_handlers(sig_handler_child, sig_handler_child);
		(fd) && (dup2(fd[1], 1), close(fd[0]), close(fd[1]));
		non_redirection(prompt, *env, prompt->file);
		prompt->exit_state = execution(prompt, env, pids);
		exit(prompt->exit_state);
	}
	else
	{
		pid_addback(pids, new_pid(pid));
		(fd) && (dup2(fd[0], 0), close(fd[0]), close(fd[1]));
	}
	return (prompt->exit_state);
}
