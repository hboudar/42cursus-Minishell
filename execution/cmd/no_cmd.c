/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/24 16:33:04 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include <signal.h>

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


// static void	here_doc2(t_prompt *prompt, int *fd, int i)
// {
//     extern int g_caught;
// 	char	*str;
//     char    *limiter;
//     setup_signal_handlers(handle_sigint, SIG_IGN);
//     close(fd[0]);
//     limiter = prompt->cmd->limiter[i];
// 	while (1)
// 	{
// 		str = readline("> ");
// 		if (str != NULL && g_caught)
// 		{
//             printf("dkhelll\n");
//             g_caught = 0;
// 			free(str);
// 			str = NULL;
//             break ;
// 		}
// 		free(str);
// 		str = NULL;
// 	}
//     restore_default_signal_handlers();
//     exit(0);
// }

// static void here_doc(t_prompt *prompt, int i)
// {
//     pid_t pid;
//     int fd[2];
//     if (pipe(fd) == -1)
//     {
//         printf("pipe error\n");
//         return ;
//     }
//     struct sigaction sa_ignore, sa_orig_int;
//     sa_ignore.sa_handler = SIG_IGN;
//     sigaction(SIGINT, &sa_ignore, &sa_orig_int);
//     pid = fork();
//     if (pid == -1)
//     {
//         printf("fork error\n");
//         close(fd[0]);
//         close(fd[1]);
//         return ;
//     }
//     if (pid == 0)
//         here_doc2(prompt, fd, i);
//     else
//     {
//         waitpid(pid, &prompt->exit_state, 0);
//         prompt->exit_state = WEXITSTATUS(prompt->exit_state);
//         (1) && (close(fd[1]), dup2(fd[0], 0));
//     }
// }


void heredoc_mode() {
    extern int g_caught;
    struct sigaction sa_ignore, sa_orig_int;
    sa_ignore.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa_ignore, &sa_orig_int);

    pid_t pid = fork();

    if (pid == 0) {

        char* heredoc_input;

        setup_signal_handlers(sigint_handler_heredoc, SIG_IGN);

        printf("Entering heredoc mode. Type 'EOF' to end.\n");

        while ((heredoc_input = readline("heredoc> ")) != NULL) {
            if (g_caught) {
                printf("Here\n");
                free(heredoc_input);
                g_caught = 0;
                break;
            }

            if (strcmp(heredoc_input, "EOF") == 0) {
                free(heredoc_input);
                break;
            }

            printf("Heredoc input: %s\n", heredoc_input);
            free(heredoc_input);
        }
        restore_default_signal_handlers();
        exit(0);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        init_signals();

    } else {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
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
        {
            heredoc_mode();
            // rl_catch_signals = 0;
        }
            // here_doc(prompt, i);
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
