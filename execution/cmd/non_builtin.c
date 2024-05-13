/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 08:43:21 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/13 20:34:13 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int	error(char *msg)
{
	perror(msg);
	return (1);
}

void ft_shell_lvl(t_env *env)
{
    t_env *tmp;
    char *str;

    tmp = env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, "SHLVL", 5))
        {
            str = ft_itoa(ft_atoi(tmp->value) + 1);
            if (!str)
                return (perror("E: ft_itoa in ft_shell_lvl"));
            if (ft_strncmp(tmp->value, "999", 3) == 0)
            {
                free(str);
                free(tmp->value);
                return ;
            }
            free(tmp->value);
            tmp->value = str;
            break ;
        }
        tmp = tmp->next;
    }
}

static void	child_process(t_prompt *prompt, t_env *env)
{
    char   *path;
    char  **envp;


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
