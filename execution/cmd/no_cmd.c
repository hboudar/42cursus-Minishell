/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/22 22:46:30 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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
    return (1);
}

static int	ft_inredirect(t_prompt *prompt, int *fd, int *fd0)
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

static void	here_doc2(t_prompt *prompt, int *fd, int i)
{
	char	*str;
    char    *limiter;

    close(fd[0]);
    limiter = prompt->cmd->limiter[i];
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
	while (1)
	{
		str = readline("> ");
        rl_clear_history();
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
        add_history(str);
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

static void here_doc(t_prompt *prompt, int i)
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
        here_doc2(prompt, fd, i);
    else
    {
        waitpid(pid, &prompt->exit_state, 0);
        prompt->exit_state = WEXITSTATUS(prompt->exit_state);
        (1) && (g_caught = 0, close(fd[1]), dup2(fd[0], 0));
    }
}

int    no_cmd(t_prompt *prompt)
{
    int fd[2];
    int fd0;
    int fd1;
    int i;

    (1) && (i = -1, fd0 = 0);
    if (prompt->cmd->type == HERE_DOC)
    {
        while (prompt->cmd->limiter[++i])
            here_doc(prompt, i);
    }
    if (pipe(fd) == -1)
        return (perror("pipe failed"), 1);
    while (prompt->cmd->file != NULL)
    {
        if (!prompt->cmd->file->type && !ft_inredirect(prompt, fd, &fd0))
            exit(1);
        else if (prompt->cmd->file->type && !ft_outredirect(prompt, fd, &fd1))
            exit(1);
        prompt->cmd->file = prompt->cmd->file->next;
    }
    (1) && (close(fd[0]), close(fd[1]));
    return (prompt->exit_state);
}
