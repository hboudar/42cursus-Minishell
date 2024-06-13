/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/12 23:36:22 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	child_process(t_prompt *prompt, t_env *env)
{
    char   *path;
    char  **envp;

    setup_signal_handlers(sig_handler_child, sig_handler_child);
    non_redirection(prompt, env, prompt->cmd->file);
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
        ignore_signals();
        pid = fork();
        if (pid == -1)
            return (error("fork failed"));
        else if (!pid)
            child_process(prompt, env);
        else
        {
            wait(&prompt->exit_state);
            prompt->exit_state = WEXITSTATUS(prompt->exit_state);
        }
    }
    else
        child_process(prompt, env);
    return (prompt->exit_state);
}
