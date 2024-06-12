/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:21:13 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/12 03:49:45 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../execution.h"

static int out_redirect(t_prompt *prompt, t_file *file, int *fd1, int quotes)
{
    printf("out_redirect\n");
    if (file && !file->data[0] && !quotes)
    {
        printf("minishell: ambiguous redirect\n");
        (*fd1 != 0) && (close(*fd1));
        prompt->exit_state = 1;
        return (0);
    }
    (*fd1 != 1) && (close(*fd1));
    if (file->type == 1)
        *fd1 = open(file->data, O_CREAT | O_RDWR | O_TRUNC, 0644);
    else if (file->type == 2)
        *fd1 = open(file->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*fd1 == -1)
    {
        printf("Error: %s: %s\n", file->data, strerror(errno));
        return (0);
    }
    else if (dup2(*fd1, 1) == -1)
    {
        close(*fd1);
        perror("dup2");
        return (0);
    }
    return (1);
}

static int in_redirect(t_prompt *prompt, t_file *file, int *fd0, int quotes)
{
    printf("in_redirect\n");
    if (file->data && !file->data[0] && !quotes)
    {
        printf("minishell: ambiguous redirect\n");
        (*fd0 != 0) && (close(*fd0));
        prompt->exit_state = 1;
        return (0);
    }
    if (file->type == 0)
        *fd0 = open(file->data, O_RDONLY);
    else if (file->type == 3)
    {
        *fd0 = open("/tmp/.doc", O_RDONLY);
        unlink("/tmp/.doc");
    }
    if (*fd0 == -1)
    {
        perror(file->data);
        prompt->exit_state = 1;
        return (0);
    }
    close(*fd0);
    return (1);
}

void redirection(t_prompt *prompt, t_env **env)
{
    t_file  *file;
    int     fd0;
	int     fd1;

    (1) && (fd0 = 0, fd1 = 1, file = prompt->cmd->file, prompt->exit_state = 0);
    while (file != NULL)
    {
        expand_string(&file->data, *env, 0);
        if ((file->type == 0 || file->type == 3)
            && !in_redirect(prompt, file, &fd0, file->quotes))
            return ;
        else if (file->type && file->type != 3
            && !out_redirect(prompt, file, &fd1, file->quotes))
            return ;
        file = file->next;
    }
    if (prompt->cmd->args != NULL)
    {
        ft_builtin(prompt, env);
        (fd1 != 1) && (close(fd1));
    }
}
