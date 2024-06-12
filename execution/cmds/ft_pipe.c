/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:16:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/12 22:07:21 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	do_left(t_prompt *prompt, t_env **env)
{
	int		fd[2];
	pid_t	pid;

	expand_cmd(prompt, *env);
	ignore_signals();
	if (pipe(fd) == -1)
		error("pipe");
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		(1) && (dup2(fd[1], 1), close(fd[0]), close(fd[1]));
		if (is_builtin(prompt))
		{
			setup_signal_handlers(sig_handler_child, sig_handler_child);
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

	expand_cmd(prompt, *env);
	ignore_signals();
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		if (is_builtin(prompt))
		{
			setup_signal_handlers(sig_handler_child, sig_handler_child);
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

int	ft_pipe(t_prompt *prompt, t_env **env)
{
	if (prompt->left->type == P_CMD)
		do_left(prompt->left, env);
	else if (prompt->left->type == P_PIPE)
		ft_pipe(prompt->left, env);
	if (prompt->right->type == P_CMD)
		prompt->exit_state = do_right(prompt->right, env);
	else if (prompt->right->type == P_PIPE)
		ft_pipe(prompt->right, env);
	return (prompt->exit_state);
}
