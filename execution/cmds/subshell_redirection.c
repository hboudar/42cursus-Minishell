/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:34:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/07 00:07:26 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

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

int    subshell_redirection(t_prompt *prompt, t_env **env, int *fd)
{
    int fd_in;
    int in;
    int fd_out;
    int out;

    (1) && (fd_in = dup(0), fd_out = dup(1), in = 0, out = 1);
    // while (prompt->file->data)
    // {
    //     if ((!prompt->file->data->type || prompt->file->data->type == 3)
    //         && !ft_redirection_in(prompt, env, &fd_in, &in))
    //         return (0);
    //     else if (prompt->file->data->type && !ft_redirection_out(prompt, env, &fd_out, &out))
    //         return (0);
    //     prompt->file = prompt->file->next;
    // }
    return (1);
}