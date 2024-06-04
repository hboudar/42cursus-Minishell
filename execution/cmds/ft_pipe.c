/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:16:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/04 14:48:11 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_child(t_prompt *prompt, t_env **env)
{
	char	**envp;
	char	*path;

	setup_signal_handlers(sig_handler_child, sig_handler_child);
	if (ft_strchr(prompt->cmd->args[0], '/') != NULL)
		path = prompt->cmd->args[0];
	else
		path = find_path(prompt->cmd->args, *env);
	envp = env_to_envp(*env, *env);
	execve(path, prompt->cmd->args, envp);
	perror(prompt->cmd->args[0]);
	exit(127);
}

void	do_left(t_prompt *prompt, t_env **env)
{
	int		fd[2];
	pid_t	pid;

	ignore_signals();
	if (pipe(fd) == -1)
		error("pipe");
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		(1) && (dup2(fd[1], 1), close(fd[0]));
		ft_child(prompt, env);
	}
	else
	{
		waitpid(pid, &prompt->exit_state, 0);
		prompt->exit_state = WEXITSTATUS(prompt->exit_state);
		(1) && (dup2(fd[0], 0), close(fd[0]), close(fd[1]));
	}
}

void	do_right(t_prompt *prompt, t_env **env)
{
	pid_t	pid;

	ignore_signals();
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
		ft_child(prompt, env);
	else
	{
		waitpid(pid, &prompt->exit_state, 0);
		prompt->exit_state = WEXITSTATUS(prompt->exit_state);
	}
}

int	ft_pipe(t_prompt *prompt, t_env **env, int *fd_out, int *fd_in)
{
	if (prompt->left->type == P_CMD)
		do_left(prompt->left, env);
	// else if (prompt->left->type == P_PIPE)
	// 	ft_pipe(prompt->left, env);
	if (prompt->right->type == P_CMD)
		do_right(prompt->right, env);
	// else if (prompt->right->type == P_PIPE)
	// 	ft_pipe(prompt->right, env);
	return (0);
}
