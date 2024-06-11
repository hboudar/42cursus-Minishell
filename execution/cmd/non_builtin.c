/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/11 20:10:35 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int  non_outredirect(t_file *file, int *fd1)
{
    printf("non_outredirect\n");
    if (file->type == 1)
        *fd1 = open(file->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (file->type == 2)
        *fd1 = open(file->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*fd1 == -1)
    {
        printf("Error: %s: %s\n", file->data, strerror(errno));
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

static int	non_inredirect(t_file *file, int *fd0)
{
    printf("non_inredirect\n");
    (*fd0 != 0) && (close(*fd0));
    if (!file->type)
        *fd0 = open(file->data, O_RDONLY);
    else if (file->type == 3)
    {
        dup2(file->fd, 0);
        close(file->fd);
        return (1);
    }
    if (*fd0 == -1)
    {
        perror(file->data);
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
    t_file *file;
    int fd0;
    int fd1;

    (void)env;
    (1) && (fd0 = 0, fd1 = 1, file = prompt->cmd->file, prompt->exit_state = 0);
    while (file != NULL)
    {
        printf("file->data: {%d}%s\n", file->type, file->data);
        printf("here\n");
        expand_string(&file->data, env, 0);
        printf("here\n");
        if (!file->data[0] && !file->quotes)
        {
            (fd0 != 0) && (close(fd0));
            (fd1 != 1) && (close(fd1));
            printf("minishell: ambiguous redirect\n");
            exit(1);
        }
        if (file->type == 3 && !non_inredirect(file, &fd0))
            exit(1);
        else if (file->type && !non_outredirect(file, &fd1))
            exit(1);
        file = file->next;
    }
}

static void	child_process(t_prompt *prompt, t_env *env)
{
    char   *path;
    char  **envp;

    printf("child process\n");
    setup_signal_handlers(sig_handler_child, sig_handler_child);
    non_redirection(prompt, env);
    if (prompt->cmd->args[0][0] == '/')
        path = prompt->cmd->args[0];
    else
        path = find_path(prompt->cmd->args, env);
    if (access(path, F_OK) == -1)
    {
        printf("minishell: %s: command not found\n", prompt->cmd->args[0]);
        exit(127);
    }
    if (access(path, X_OK) == -1)
    {
        printf("minishell: %s: permission denied\n", prompt->cmd->args[0]);
        exit(126);
    }
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
        printf("executing none builtin\n");
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
