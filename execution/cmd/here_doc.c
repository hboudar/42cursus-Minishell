/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:58:30 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/25 21:12:13 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static void	here_doc2(t_prompt *prompt, int *fd, int i)
{
    extern int g_caught;
	char	*str;
    char    *limiter;

    close(fd[0]);
    limiter = prompt->cmd->limiter[i];
    setup_signal_handlers(sigint_handler_heredoc, SIG_IGN);
    while (1)
    {
        str = readline("> ");
        if (g_caught || (!ft_strncmp(str, limiter, ft_strlen(limiter))
            && ft_strlen(str) == ft_strlen(limiter)))
        {
            g_caught = 0;
            free(str);
            break;
        }
        free(str);
    }
    restore_default_signal_handlers();
    exit(0);
}

void here_doc(t_prompt *prompt, int i, int *fd)
{
    extern int g_caught;
    pid_t pid;
    struct sigaction sa_ignore, sa_orig_int;

    sa_ignore.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa_ignore, &sa_orig_int);
    sigaction(SIGQUIT, &sa_ignore, &sa_orig_int);
    g_caught = 0;
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return ;
    }
    pid = fork();
    if (pid == 0)
        here_doc2(prompt, fd, i);
    else if (pid > 0)
    {
        waitpid(pid, &prompt->exit_state, 0);
        prompt->exit_state = WEXITSTATUS(prompt->exit_state);
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
}
