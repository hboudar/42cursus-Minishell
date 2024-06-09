/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:58:30 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/09 20:05:16 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void ignore_signals(void)
{
    struct sigaction sa_ignore;
    struct sigaction sa_orig_int;

    sa_ignore.sa_handler = SIG_IGN;
    sigaction(SIGINT, &sa_ignore, &sa_orig_int);
    sigaction(SIGQUIT, &sa_ignore, &sa_orig_int);
}

static void	here_doc2(t_prompt *prompt, char *limiter, int quotes, int fd)
{
    extern int g_caught;
	char	*str;

    setup_signal_handlers(sigint_handler_heredoc, SIG_IGN);
    while (1)
    {
        str = readline("> ");
        //expanding the variables
        if (g_caught || (!ft_strncmp(str, limiter, ft_strlen(limiter))
            && ft_strlen(str) == ft_strlen(limiter)) || !str)
        {
            if (str)
                free(str);
            break;
        }
        write(fd, str, ft_strlen(str));
        write(fd, "\n", 1);
        free(str);
		close(fd);
    }
    exit(0);
}

void	here_doc1(t_prompt *p, t_file *file, t_limiter *lim)
{
	extern int	g_caught;
	pid_t	pid;

	(1) && (unlink("/tmp/.doc"), g_caught = 0);
	file->fd = open("/tmp/.doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (file && file->type != 3)
		file = file->next;
	if (!file)
		return ;
	ignore_signals();
	pid = fork();
	if (pid == 0)
		here_doc2(file, lim->limit, lim->quotes, file->fd);
	else
	{
		waitpid(pid, &p->exit_state, 0);
		p->exit_state = WEXITSTATUS(p->exit_state);
		g_caught = (p->exit_state == 1);
		file->type = 0;
        here_doc1(p, file->next, lim->next);
	}
}

void	here_doc(t_prompt *prompt)
{
	if (prompt->subshell)
	{
		here_doc1(prompt, prompt->file, prompt->limiter);
		if (prompt->exit_state != 0)
			return ;
	}
	if (prompt->type == P_CMD)
	{
		here_doc1(prompt, prompt->cmd->file, prompt->cmd->limiter);
		if (prompt->exit_state != 0)
			return ;
	}
	else
	{
		here_doc(prompt->left);
		if (prompt->exit_state != 0)
			return ;
		here_doc(prompt->right);
	}
}
