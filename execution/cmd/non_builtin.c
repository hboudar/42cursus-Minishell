/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/11 19:08:10 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int  non_outredirect(t_prompt *prompt, int *fd1)
{
    if (prompt->cmd->file->type == 1)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (prompt->cmd->file->type == 2)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*fd1 == -1)
    {
        printf("Error: %s: %s\n", prompt->cmd->file->next->data, strerror(errno));
        return (0);
    }
    if (dup2(*fd1, 1) == -1)
    {
        close(*fd1);
        perror("dup2 in out");
        return (0);
    }
    return (1);
}

static int	non_inredirect(t_prompt *prompt, int *fd0)
{
    (*fd0 != 0) && (close(*fd0));
    if (!prompt->cmd->file->type)
        *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    else if (prompt->cmd->file->type == 3)
    {
        printf("here %d\n", prompt->cmd->file->fd);
        dup2(prompt->cmd->file->fd, 0);
        close(prompt->cmd->file->fd);
        return (1);
    }
    if (*fd0 == -1)
    {
        perror(prompt->cmd->file->data);
        return (0);
    }
    if (dup2(*fd0, 0) == -1)
    {
        close(*fd0);
        perror("dup2 in in");
        return (0);
    }
    return (1);
}

static void non_redirection(t_prompt *prompt, t_env *env)
{
    int fd0;
    int fd1;

    (1) && (fd0 = 0, fd1 = 1, prompt->exit_state = 0);
    while (prompt->cmd->file != NULL)
    {
        expand_string(&prompt->cmd->file->data, env, 0);
        if (!prompt->cmd->file->data[0] && !prompt->cmd->file->quotes)
        {
            (fd0 != 0) && (close(fd0));
            (fd1 != 1) && (close(fd1));
            printf("minishell: ambiguous redirect\n");
            exit(1);
        }
        if ((!prompt->cmd->file->type || prompt->cmd->file->type == 3)
            && !non_inredirect(prompt, &fd0))
            exit(1);
        else if (prompt->cmd->file->type && !non_outredirect(prompt, &fd1))
            exit(1);
        prompt->cmd->file = prompt->cmd->file->next;
    }
}

static void	child_process(t_prompt *prompt, t_env *env)
{
    char   *path;
    char  **envp;

    setup_signal_handlers(sig_handler_child, sig_handler_child);
    non_redirection(prompt, env);
    if (prompt->cmd->args[0][0] == '/')
        path = prompt->cmd->args[0];
    else
        path = find_path(prompt->cmd->args, env);
    envp = env_to_envp(env, env);
    execve(path, prompt->cmd->args, envp);
    perror(prompt->cmd->args[0]);
    exit(127);
}

int    execute_nonebuiltin(t_prompt *prompt, t_env *env, int mode)
{
    pid_t	    pid;

    if (!mode)
    {
        ignore_signals();
        pid = fork();
        if (pid == -1)
            return (error("fork failed"));
        else if (!pid)
            child_process(prompt, env);
        else
        {
            waitpid(pid, &prompt->exit_state, 0);
            prompt->exit_state = WEXITSTATUS(prompt->exit_state);
        }
    }
    else
        child_process(prompt, env);
    return (prompt->exit_state);
}
