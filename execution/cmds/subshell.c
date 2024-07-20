/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:51:45 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/19 17:27:41 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	subshell(t_prompt *prompt, t_env **env, int *fd, t_pid **pids)
{
	pid_t	pid;

	prompt->subshell = 0;
	setup_signal_handlers(sig_handler_child, sig_handler_child);
	pid = fork();
	if (pid == -1)
		ft_putstr_fd("fork\n", 2);
	if (pid == 0)
	{
		(fd) && (dup2(fd[1], 1), close(fd[0]), close(fd[1]));
		none_redirection(prompt, *env, prompt->file);
		prompt->exit_state = prep_execution(prompt, env, 1);
		exit(prompt->exit_state);
	}
	else
	{
		ignore_signals();
		pid_addback(pids, new_pid(pid));
		(fd) && (dup2(fd[0], 0), close(fd[0]), close(fd[1]));
	}
	return (prompt->exit_state);
}
