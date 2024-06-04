/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:26:19 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/04 18:15:40 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int    no_cmd(t_prompt *prompt, t_env **env)
{
    extern int g_caught;
    int fd[2];
    int i;

    (1) && (i = -1, fd[0] = 0, fd[1] = 1, g_caught = 0);
    while (prompt->cmd->type == HERE_DOC && !g_caught && prompt->cmd->limiter[++i])
        here_doc(prompt, i, fd);
    if (fd[0] != 0)
        close(fd[0]);
    if (g_caught)
    {
        g_caught = 0;
        return (1);
    }
    redirection(prompt, env);
    return (prompt->exit_state);
}

int	execute_builtin(t_prompt *prompt, t_env **env)
{
    extern int g_caught;
    int	fd[2];
    int i;

	(1) && (i = -1, fd[0] = 0, fd[1] = 1, g_caught = 0);
    while (prompt->cmd->type == HERE_DOC && !g_caught && prompt->cmd->limiter[++i])
        here_doc(prompt, i, fd);
    if (g_caught)
    {
        g_caught = 0;
        return (1);
    }
    else
        close(fd[0]);
    redirection(prompt, env);
	return (prompt->exit_state);
}

int	ft_cmd(t_prompt *prompt, t_env **env)
{
    printf("FT_CMD\n");
	expand_cmd(prompt, *env);
	if (!prompt->cmd)
	{
		perror("malloc");
		return (1);
	}
    if (!prompt->cmd->args)
		return (no_cmd(prompt, env));
	else if (is_builtin(prompt))
		return (execute_builtin(prompt, env));
	return (execute_nonebuiltin(prompt, *env));
}
