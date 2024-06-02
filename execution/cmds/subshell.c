/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:35:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/31 18:58:47 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int		subshell(t_prompt *prompt, t_env **env)
{
    extern int g_caught;
    int fd[2];
    int i;

    (1) && (i = -1, g_caught = 0, fd[0] = 0, fd[1] = 1);
    while (prompt->cmd->type == HERE_DOC && !g_caught && prompt->cmd->limiter[++i])
        here_doc(prompt, i, fd);
    if (g_caught)
        return (1);
    ignore_signals();
    subshell_redirection(prompt, env);

 
    if (prompt->type == P_PIPE)
        subshell_pipe(prompt, env);
    else if (prompt->type == P_OR)
        subshell_or(prompt, env);
    else if (prompt->type == P_AND)
        subshell_and(prompt, env);
    return (0);
}


//expand_cmd