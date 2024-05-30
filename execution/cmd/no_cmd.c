/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/29 23:37:43 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int  no_outredirect(t_prompt *prompt, int *fd, int *fd1)
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
    close(*fd1);
    return (1);
}

static int	no_inredirect(t_prompt *prompt, int *fd, int *fd0)
{
    *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    if (*fd0 == -1)
    {
        close(fd[0]);
        close(fd[1]);
        perror(prompt->cmd->file->data);
        return (0);
    }
    close(*fd0);
    return (1);
}

int    no_cmd(t_prompt *prompt)
{
    extern int g_caught;
    int fd[2];
    int fd0;
    int fd1;
    int i;

    (1) && (i = -1, g_caught = 0);
    while (prompt->cmd->type == HERE_DOC && !g_caught && prompt->cmd->limiter[++i])
        here_doc(prompt, i, fd);
    if (g_caught)
        g_caught = 0;
    if (prompt->cmd->type != HERE_DOC && pipe(fd) == -1)
        return (perror("pipe failed"), 1);
    while (prompt->cmd->file != NULL)
    {
        if (!prompt->cmd->file->type && !no_inredirect(prompt, fd, &fd0))
            return (1);
        else if (prompt->cmd->file->type && !no_outredirect(prompt, fd, &fd1))
            return (1);
        prompt->cmd->file = prompt->cmd->file->next;
    }
    (1) && (close(fd[0]), close(fd[1]));
    return (prompt->exit_state);
}
