/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:16:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/02 15:44:11 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	do_cmd(t_prompt *prompt, t_env **env, int *fd_out, int *fd_in)
{
	pid_t pid;
	int fd[2];

	if (pipe(fd) == -1)
		return (error("pipe"));
	pid = fork();
	if (pid == -1)
		return (error("fork"));
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], *fd_out);
		close(fd[1]);
		exit(ft_cmd(prompt, env));
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], *fd_in);
		close(fd[0]);
	}
	return (0);
}

int	do_pipe(t_prompt *prompt, t_env **env, int *fd_out, int *fd_in)
{
	
}

int ft_pipe(t_prompt *prompt, t_env **env, int *fd_out, int *fd_in)
{
	int fd[2];
	pid_t pid;

	if (prompt->type == P_PIPE)
	{
		if (pipe(fd) == -1)
			return (error("pipe"));
		pid = fork();
		if (pid == -1)
			return (error("fork"));
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], *fd_out);
			close(fd[1]);
			return (ft_pipe(prompt->left, env, fd_out, fd_in));
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], *fd_in);
			close(fd[0]);
			return (ft_pipe(prompt->right, env, fd_out, fd_in));
		}
	}
	else
		return (do_cmd(prompt, env, fd_out, fd_in));
	return (0);
}

//expand_cmd