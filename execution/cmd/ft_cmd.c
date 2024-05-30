/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:26:19 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/30 20:17:33 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int    no_cmd(t_prompt *prompt, t_env **env)
{
    int real_in;
    int real_out;
    extern int g_caught;
    int fd[2];
    int i;

    real_in = dup(0);
    real_out = dup(1);
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
    (1) && (dup2(real_in, 0), dup2(real_out, 1));
    (1) && (close(real_in), close(real_out));
    return (prompt->exit_state);
}

int	execute_builtin(t_prompt *prompt, t_env **env)
{
    extern int g_caught;
    int	real_in;
	int	real_out;
    int	fd[2];
    int i;
    
    real_in = dup(0);
    real_out = dup(1);
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
    (1) && (dup2(real_in, 0), close(real_in));
    (1) && (dup2(real_out, 1), close(real_out));
	return (prompt->exit_state);
}
