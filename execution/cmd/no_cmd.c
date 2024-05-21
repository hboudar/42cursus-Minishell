/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/20 18:35:42 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"


static int ft_outfile(t_prompt *prompt)
{
    int fd;

    if (prompt->cmd->file->appendable)
    {
        fd = open(prompt->cmd->file->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            printf ("%s: %s\n", prompt->cmd->file->data, strerror(errno));
            prompt->exit_state = 1;
            return (-1);
        }
    }
    else
    {
        fd = open(prompt->cmd->file->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            printf ("%s: %s\n", prompt->cmd->file->data, strerror(errno));
            prompt->exit_state = 1;
            return (-1);
        }
    }
    return (fd);
}


static void ft_redirect(t_prompt *prompt)
{
    t_prompt *tmp;
    int fd;

    if (!prompt->cmd->file)
        return ;
    tmp = prompt;
    while (tmp->cmd->file)
    {
        if (tmp->cmd->file->type == 0 && open(tmp->cmd->file->data, O_RDONLY) == -1)
        {
            printf ("%s: %s\n", tmp->cmd->file->data, strerror(errno));
            prompt->exit_state = 1;
            return ;
        }
        else if (tmp->cmd->file->type == 1)
        {
            fd = ft_outfile(tmp);
            if (fd == -1)
                return ;
        }
        tmp->cmd->file = tmp->cmd->file->next;
    }
}

static void	here_doc2(t_prompt *prompt, int *fd)
{
	char	*str;
    char    *limiter;

    close(fd[0]);
    limiter = prompt->cmd->limiter[0];
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
	while (1)
	{
		str = readline("> ");
		if ((ft_strlen(str) == ft_strlen(limiter)
			&& !ft_strncmp(str, limiter, ft_strlen(limiter))) || !str)
		{
			free(str);
			str = NULL;
            break ;
		}
		free(str);
		str = NULL;
	}
    return ;
}

static void here_doc(t_prompt *prompt)
{
    extern int g_caught;
    pid_t pid;
    int fd[2];

    if (pipe(fd) == -1)
    {
        printf("pipe error\n");
        return ;
    }
    (1) && (g_caught = 2, pid = fork());
    if (pid == -1)
    {
        printf("fork error\n");
        close(fd[0]);
        close(fd[1]);
        return ;
    }
    if (pid == 0)
        here_doc2(prompt, fd);
    else
    {
        waitpid(pid, &prompt->exit_state, 0);
        prompt->exit_state = WEXITSTATUS(prompt->exit_state);
        (1) && (g_caught = 0, close(fd[1]), dup2(fd[0], 0));
    }
}

int    no_cmd(t_prompt *prompt)
{
    int i;

    if (prompt->cmd->type == HERE_DOC)
    {
        i = 0;
        while (prompt->cmd->limiter[i])
        {
            here_doc(prompt);
            i++;
        }
    }
    ft_redirect(prompt);
    return (prompt->exit_state);
}
