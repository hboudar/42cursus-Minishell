/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/20 19:44:56 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	error(char *msg)
{
	perror(msg);
	return (1);
}

/*void	first_process(char *av[], char *envp[], t_pipex *pi)
{
	if (pipe(pi->fd) == -1)
		error("pipe");
	pi->pid = fork();
	if (pi->pid == -1)
		error("fork");
	if (pi->pid == 0)
	{
		pi->infile = open(av[1], O_RDONLY);
		if (pi->infile == -1)
		{
			close(pi->fd[0]);
			close(pi->fd[1]);
			error("infile");
		}
		check_files(dup2(pi->infile, 0), dup2(pi->fd[1], 1),
			close(pi->fd[0]), 0);
		execute(av[2], envp);
	}
	else
	{
		if (waitpid(pi->pid, NULL, 0) == -1)
			error("waitpid function");
		check_files(dup2(pi->fd[0], 0), 0, close(pi->fd[1]), close(pi->fd[0]));
	}
}*/

static int	ft_inredirect(t_prompt *prompt, int *fd, int *fd0)
{
    if (prompt->cmd->file->type == IN)
    {
        *fd0 = open(prompt->cmd->file->file, O_RDONLY);
        if (*fd0 == -1)
        {
            close(fd[0]);
            close(fd[1]);
            perror(prompt->cmd->file->file);
            return (-1);
        }
        if (dup2(*fd0, 0) == -1)
        {
            close(fd[0]);
            close(fd[1]);
            close(*fd0);
            perror("dup2");
            return (-1);
        }
    }
    return (0);
}

static void	child_process(t_prompt *prompt, t_env *env, int *fd)
{
    int   fd0;
    int   fd1;
    char   *path;
    char  **envp;

    if (prompt->cmd->file)
    {
        if (ft_inredirect(prompt, fd, &fd0) == -1)
            exit(1);
        if (ft_outredirect(prompt, fd, &fd1) == -1)
            exit(1);
    }
    path = find_path(prompt->cmd->args, env);
    envp = env_to_envp(env, env);
    if (execve(path, prompt->cmd->args, envp) == -1)
    {
        perror(prompt->cmd->args[0]);
        free(path);
        free_envp(envp);
        exit(127);
    }
}

int    execute_nonebuiltin(t_prompt *prompt, t_env *env)
{
    int     status;
    int     fd[2];
    pid_t	pid;

    if (pipe(fd) == -1)
        return (error("pipe failed"));
    pid = fork();
    if (pid == -1)
        return (error("fork failed"));
    else if (pid == 0)
        child_process(prompt, env, fd);
    else
    {
        status = waitpid(pid, &prompt->exit_state, 0);
        prompt->exit_state = WEXITSTATUS(prompt->exit_state);
        if (status == -1)
            return (error("waitpid failed"));
    }
    return (0);
}
