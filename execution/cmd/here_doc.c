/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:58:30 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/11 20:27:05 by hboudar          ###   ########.fr       */
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

static void	here_doc2(char *limiter, int fd, int quotes, t_env *env)
{
    extern int g_caught;
	char	*str;

    setup_signal_handlers(sigint_handler_heredoc, SIG_IGN);
    while (1)
    {
        str = readline("> ");
        if (g_caught || (!ft_strncmp(str, limiter, ft_strlen(limiter))
            && ft_strlen(str) == ft_strlen(limiter)) || !str)
        {
            if (str)
                free(str);
            break;
        }
		expand_string(&str, env, quotes);
        write(fd, str, ft_strlen(str));
        write(fd, "\n", 1);
        free(str);
    }
    exit(0);
}

void	here_doc1(t_prompt *prompt, t_file *file, t_limiter *lim, t_env *env)
{
	extern int	g_caught;
	pid_t	pid;

	(1) && (unlink("/tmp/.doc"), g_caught = 0);
	g_caught = 0;
	while (file && file->type != 3)
		file = file->next;
	if (!file)
		return ;
	file->fd = open("here", O_RDWR | O_CREAT | O_TRUNC, 0644);
	unlink("here");
	ignore_signals();
	pid = fork();
	if (pid == 0)
		here_doc2(lim->limit, file->fd, lim->quotes , env);
	else
	{
		waitpid(pid, &prompt->exit_state, 0);
		prompt->exit_state = WEXITSTATUS(prompt->exit_state);
		close(file->fd);
		file->fd = open("here", O_RDONLY);
		g_caught = (prompt->exit_state == 1);
        if (g_caught)
            return ;
        here_doc1(prompt, file->next, lim->next, env);
	}
}

void	here_doc(t_prompt *prompt, t_env *env)
{
	if (prompt->subshell)
	{
        if (!prompt->limiter)
            return ;
		here_doc1(prompt, prompt->file, prompt->limiter, env);
	}
	if (prompt->type == P_CMD)
	{
        if (!prompt->cmd->limiter)
            return ;
		here_doc1(prompt, prompt->cmd->file, prompt->cmd->limiter, env);
	}
	else
	{
		if (prompt->exit_state != 0)
			return ;
		here_doc(prompt->left, env);
		if (prompt->exit_state != 0)
			return ;
		here_doc(prompt->right, env);
	}
}
