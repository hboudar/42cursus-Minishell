/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:21:13 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/09 20:08:22 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../execution.h"

static int out_redirect(t_prompt *prompt, int *fd1)
{
    if (prompt->cmd->file->type == 1)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (prompt->cmd->file->type == 2)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*fd1 == -1)
    {
        printf("Error: %s: %s\n", prompt->cmd->file->data, strerror(errno));
        return (0);
    }
    if (!prompt->cmd->args)
        close(*fd1);
    else if (dup2(*fd1, 1) == -1)
    {
        close(*fd1);
        perror("dup2");
        return (0);
    }
    return (1);
}

static int in_redirect(t_prompt *prompt, int *fd0)
{
    if (!prompt->cmd->args && !prompt->cmd->file->type)
        *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    else if (!prompt->cmd->file->type)
    {
        (*fd0 != 0) && (close(*fd0));
        *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    }
    if (*fd0 == -1)
    {
        perror(prompt->cmd->file->data);
        return (0);
    }
    if (!prompt->cmd->args)
        close(*fd0);
    return (1);
}

void redirection(t_prompt *prompt, t_env **env)
{
    int	fd0;
	int	fd1;

    (1) && (fd0 = 0, fd1 = 1, prompt->exit_state = 0);
    while (prompt->cmd->file != NULL)
    {
        if ((!prompt->cmd->file->type || prompt->cmd->file->type == 3)
            && !in_redirect(prompt, &fd0))
        {
            prompt->exit_state = 1;
            return ;
        }
        else if (prompt->cmd->file->type && !out_redirect(prompt, &fd1))
        {
            prompt->exit_state = 1;
            return ;
        }
        prompt->cmd->file = prompt->cmd->file->next;
    }
    if (prompt->cmd->args != NULL)
    {   
        prompt->exit_state = ft_builtin(prompt, env);
        (fd0 != 0) && (close(fd0));
        (fd1 != 1) && (close(fd1));
    }
}
