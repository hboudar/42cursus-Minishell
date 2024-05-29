/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/29 12:02:03 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
    if (dup2(*fd1, 1) == -1)
    {
        close(fd[0]);
        close(fd[1]);
        close(*fd1);
        perror("dup2 in out");
        return (0);
    }
    return (1);
}

static int	ft_inredirect(t_prompt *prompt, int *fd, int *fd0)
{
    if (!prompt->cmd->file->type)
    {
        (*fd0 != 0) && (close(*fd0));
        *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    }
    else
    {
        if (dup2(fd[0], *fd0) == -1)
            return (printf("failed dup2"),0);
    }
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
        perror("dup2 in in");
        return (0);
    }
    return (1);
}

static void ft_redirection(t_prompt *prompt, int *fd, int *fd0, int *fd1)
{
    *fd0 = 0;
    *fd1 = 1;
    while (prompt->cmd->file != NULL)
    {
        if ((!prompt->cmd->file->type || prompt->cmd->file->type == 3)
            && !ft_inredirect(prompt, fd, fd0))
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

    setup_signal_handlers(sig_handler_child, sig_handler_child);
    ft_redirection(prompt, fd, &fd0, &fd1);
    if (prompt->cmd->args[0][0] == '/')
        path = prompt->cmd->args[0];
    else
        path = find_path(prompt->cmd->args, env);
    envp = env_to_envp(env, env);
    execve(path, prompt->cmd->args, envp);
    perror(prompt->cmd->args[0]);
    exit(127);
}

int    execute_nonebuiltin(t_prompt *prompt, t_env *env)
{
    extern int g_caught;
    int     fd[2];
    pid_t	pid;
    int     i;

    (1) && (i = -1, g_caught = 0, fd[0] = 0, fd[1] = 1);
    while (prompt->cmd->type == HERE_DOC && !g_caught && prompt->cmd->limiter[++i])
        here_doc(prompt, i, fd);
    if (g_caught)
        return (1);
    ignore_signals();
    pid = fork();
    if (pid == -1)
        return (error("fork failed"));
    else if (!pid)
        child_process(prompt, env, fd);
    else
    {
        waitpid(pid, &prompt->exit_state, 0);
        prompt->exit_state = WEXITSTATUS(prompt->exit_state);
        (fd[0] != 0) && (close(fd[0]));
        (fd[1] != 1) && (close(fd[1]));
    }
    return (prompt->exit_state);
}
