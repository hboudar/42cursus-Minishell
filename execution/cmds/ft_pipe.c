/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:16:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 00:02:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	do_left(t_prompt *prompt, t_env **env, int *fd)
{
	pid_t	pid;

	ignore_signals();
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		(1) && (dup2(fd[1], 1), close(fd[0]), close(fd[1]));
		if (is_builtin(prompt))
		{
			setup_signal_handlers(sig_handler_child, SIG_IGN);
			exit(ft_builtin(prompt, env));
		}
		else
			execute_nonebuiltin(prompt, *env, 1);
	}
	else
	{
		wait(&prompt->exit_state);	
		prompt->exit_state = WEXITSTATUS(prompt->exit_state);
		(1) && (dup2(fd[0], 0), close(fd[0]), close(fd[1]));
	}
}

int	do_right(t_prompt *prompt, t_env **env)
{
	pid_t	pid;

	ignore_signals();
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		if (is_builtin(prompt))
		{
			setup_signal_handlers(sig_handler_child, SIG_IGN);
			exit(ft_builtin(prompt, env));
		}
		else
			execute_nonebuiltin(prompt, *env, 1);
	}
	else
	{
		wait(&prompt->exit_state);
		prompt->exit_state = WEXITSTATUS(prompt->exit_state);
	}
	return (prompt->exit_state);
}

int	ft_pipe(t_prompt *prompt, t_env **env, char side)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error("pipe");
	if (prompt->subshell)
		prompt->exit_state = subshell(prompt, env, fd);
	else if (prompt->type == P_CMD)
	{
		expand_cmd(prompt, *env);
		(side == 'L') && (do_left(prompt, env, fd), side = 'L');
		(side == 'R') && (do_right(prompt, env), side = 'R');
	}
	return (prompt->exit_state);
}
