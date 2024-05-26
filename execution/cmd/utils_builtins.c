/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 08:46:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/26 19:56:56 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


static int  ft_outredirect(t_prompt *prompt, int *fd, int *fd1)
{
    printf("ft_outredirect\n");
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
        perror("dup2");
        return (0);
    }
    close(*fd1);
    *fd1 = 1;
    return (1);
}

static int	ft_inredirect(t_prompt *prompt, int *fd, int *fd0)
{
    printf("ft_inredirect\n");
    if (!prompt->cmd->file->type)
    {
        (*fd0 != 0) && (close(*fd0));
        *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    }
    else if (dup2(fd[0], *fd0) == -1)
            return (printf("failed dup2"),0);
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
        perror("dup2");
        return (0);
    }
    return (1);
}
static int ft_redirection(t_prompt *prompt, int *fd, int *fd0, int *fd1)
{
    *fd0 = 0;
    *fd1 = 1;
    while (prompt->cmd->file != NULL)
    {
        if ((!prompt->cmd->file->type || prompt->cmd->file->type == 3)
            && !ft_inredirect(prompt, fd, fd0))
            return (1);
        else if (prompt->cmd->file->type && !ft_outredirect(prompt, fd, fd1))
            return (1);
        prompt->cmd->file = prompt->cmd->file->next;
    }
    return (0);
}

int	execute_builtin(t_prompt *prompt, t_env **env)
{
    extern int g_caught;
    int	fd[2];
	int	fd0;
	int	fd1;
    int i;

	(1) && (i = -1, g_caught = 0);
    // while (prompt->cmd->type == HERE_DOC && !g_caught && prompt->cmd->limiter[++i])
    //     here_doc(prompt, i, fd);
    if (g_caught)
    {
        printf("g_caught\n");
        close(fd[0]);
        return (1);
    }
    printf("b:here\n");
    if (ft_redirection(prompt, fd, &fd0, &fd1))
        return (1);
    printf("a:here\n");
	prompt->exit_state = ft_builtin(prompt, env);
    (fd0 != 0) && (close(fd0));
    (fd1 != 1) && (close(fd1));
	return (prompt->exit_state);
}
