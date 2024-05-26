/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/26 10:53:54 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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

static int  ft_outredirect(t_prompt *prompt, int *fd, int *fd1)
{
    if (prompt->cmd->file->type == 1)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (prompt->cmd->file->type == 2)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*fd1 == -1)
    {
        printf("Error: %s: %s\n", prompt->cmd->file->next->data, strerror(errno));
        close(fd[0]);
        close(fd[1]);
        return (0);
    }
    if (dup2(*fd1, 1) == -1 || dup2(fd[0], 0) == -1)
    {
        close(fd[0]);
        close(fd[1]);
        close(*fd1);
        perror("dup2");
        return (0);
    }
    return (1);
}

static int	ft_inredirect(t_prompt *prompt, int *fd, int *fd0)
{
    printf("time\n");
    if (*fd0 != 0)
        close(*fd0);
    *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    if (*fd0 == -1)
    {
        close(fd[0]);
        close(fd[1]);
        perror(prompt->cmd->file->data);
        return (0);
    }
    if (dup2(*fd0, 0) == -1)
    {
        close(fd[0]);
        close(fd[1]);
        close(*fd0);
        perror("dup2");
        return (0);
    }
    close(fd[0]);
    return (1);
}

static void ft_redirection(t_prompt *prompt, int *fd, int *fd0, int *fd1)
{
    while (prompt->cmd->file != NULL)
    {
        if (!prompt->cmd->file->type && !ft_inredirect(prompt, fd, fd0))
            exit(1);
        else if (prompt->cmd->file->type && !ft_outredirect(prompt, fd, fd1))
            exit(1);
        prompt->cmd->file = prompt->cmd->file->next;
    }
}

static void	child_process(t_prompt *prompt, t_env *env, int *fd)
{
    int   fd0;
    int   fd1;
    char   *path;
    char  **envp;

    fd0 = 0;
    ft_redirection(prompt, fd, &fd0, &fd1);
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
    extern int g_caught;
    int     fd[2];
    int     i;
    pid_t	pid;

    (1) && (i = -1, g_caught = 0);
    while (!g_caught && prompt->cmd->type == HERE_DOC && prompt->cmd->limiter[++i])
        here_doc(prompt, i, fd);
    pid = fork();
    if (pid == -1)
        return (error("fork failed"));
    else if (!pid)
    {
        close(fd[1]);
        child_process(prompt, env, fd);
    }
    else
    {
        waitpid(pid, &prompt->exit_state, 0);
        prompt->exit_state = WEXITSTATUS(prompt->exit_state);
        (prompt->cmd->limiter) && (close(fd[0]), close(fd[1]));
    }
    return (0);
}
