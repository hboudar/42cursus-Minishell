/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 08:46:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/29 23:37:15 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


static int  builtin_outredirect(t_prompt *prompt, int *fd, int *fd1)
{
    if (prompt->cmd->file->type == 1)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (prompt->cmd->file->type == 2)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*fd1 == -1)
    {
        printf("Error: %s: %s\n", prompt->cmd->file->data, strerror(errno));
        close(fd[0]);
        close(fd[1]);
        return (0);
    }
    if (dup2(*fd1, 1) == -1)
    {
        close(fd[0]);
        close(fd[1]);
        close(*fd1);
        perror("dup2");
        return (0);
    }
    return (1);
}

static int	builtin_inredirect(t_prompt *prompt, int *fd, int *fd0)
{
    if (!prompt->cmd->file->type)
    {
        (*fd0 != 0) && (close(*fd0));
        *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    }
    if (*fd0 == -1)
    {
        close(fd[0]);
        close(fd[1]);
        perror(prompt->cmd->file->data);
        return (0);
    }
    return (1);
}

static int builtin_redirection(t_prompt *prompt, t_env **env, int *fd)
{
    int	real_in;
	int	real_out;
    int	fd0;
	int	fd1;

    (1) && (fd0 = 0, fd1 = 1);
    real_in = dup(0);
    real_out = dup(1);
    while (prompt->cmd->file != NULL)
    {
        if ((!prompt->cmd->file->type || prompt->cmd->file->type == 3)
            && !builtin_inredirect(prompt, fd, &fd0))
            return (1);
        else if (prompt->cmd->file->type && !builtin_outredirect(prompt, fd, &fd1))
            return (1);
        prompt->cmd->file = prompt->cmd->file->next;
    }
    prompt->exit_state = ft_builtin(prompt, env);
    (fd0 != 0) && (close(fd0));
    (fd1 != 1) && (close(fd1));
    (1) && (dup2(real_in, 0), close(real_in));
    (1) && (dup2(real_out, 1), close(real_out));
    return (0);
}

int	execute_builtin(t_prompt *prompt, t_env **env)
{
    extern int g_caught;
    int	fd[2];
    int i;
    
    
	(1) && (i = -1, g_caught = 0);
    while (prompt->cmd->type == HERE_DOC && !g_caught && prompt->cmd->limiter[++i])
        here_doc(prompt, i, fd);
    if (g_caught)
    {
        close(fd[0]);
        return (1);
    }
    if (builtin_redirection(prompt, env, fd))
        return (1);
	return (prompt->exit_state);
}
