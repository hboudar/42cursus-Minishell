/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/09 16:43:02 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	error(char *msg)
{
	perror(msg);
	return (1);
}

static void	child_process(t_prompt *prompt, t_env *env)
{
    char   *path;
    char  **envp;

    path = find_path(prompt->cmd->args, env);
    if (!path)
        exit(1);
    envp = env_to_envp(env);
    if (execve(path, prompt->cmd->args, envp) == -1)
    {
        perror("execve failed");
        free(path);
        free_envp(envp);
        exit(1);
    }
}

int    execute_nonebuiltin(t_prompt *prompt, t_env *env)
{
    int     status;
    pid_t	pid;

    pid = fork();
    if (pid == -1)
        return (error("fork failed"));
    else if (pid == 0)
        child_process(prompt, env);
    else
    {
        status = waitpid(pid, &prompt->exit_state, 0);
        prompt->exit_state = WEXITSTATUS(prompt->exit_state);
        if (status == -1)
            return (error("waitpid failed"));
    }
    return (0);
}
