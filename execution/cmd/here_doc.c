/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:58:30 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 12:04:08 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	here_doc0(t_prompt *prompt, t_file *file, t_limiter *lim, t_env *env);

void	ignore_signals(void)
{
	struct sigaction	sa_ignore;
	struct sigaction	sa_orig_int;

	sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_ignore, &sa_orig_int);
	sigaction(SIGQUIT, &sa_ignore, &sa_orig_int);
}

static void	here_doc3(char *limiter, int fd, int quotes, t_env *env)
{
	extern int	g_caught;
	char		*str;

	setup_signal_handlers(sigint_handler_heredoc, SIG_IGN);
	while (1)
	{
		str = readline("> ");
		if (g_caught || (!ft_strncmp(str, limiter, ft_strlen(limiter))
				&& ft_strlen(str) == ft_strlen(limiter)) || !str)
		{
			if (str)
				free(str);
			close(fd);
			break ;
		}
		expand_string(&str, env, quotes, NULL);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	exit(0);
}

void	here_doc1(t_prompt *prompt, t_file *file, t_limiter *lim, t_env *env)
{
	extern int	g_caught;
	pid_t		pid;
	int			fd;

	fd = open("/tmp/.doc", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	file->fd = open("/tmp/.doc", O_RDONLY);
	ignore_signals();
	pid = fork();
	if (pid == 0)
		here_doc3(lim->limit, fd, lim->quotes, env);
	else
	{
		waitpid(pid, &prompt->exit_state, 0);
		prompt->exit_state = WEXITSTATUS(prompt->exit_state);
		(1) && (close(fd), close(file->fd),
			file->fd = open("/tmp/.doc", O_RDONLY), unlink("/tmp/.doc"));
		g_caught = (prompt->exit_state == 1) * 2;
		if (g_caught)
			close(file->fd);
		if (!g_caught && file->next && file->next->type == 3)
		{
			close(file->fd);
			here_doc0(prompt, file->next, lim->next, env);
		}
	}
}

void	here_doc0(t_prompt *prompt, t_file *file, t_limiter *lim, t_env *env)
{
	extern int	g_caught;

	while (file && file->type != 3)
		file = file->next;
	if (!file)
		return ;
	else
	{
		g_caught = 0;
		unlink("/tmp/.doc");
		here_doc1(prompt, file, lim, env);
	}
}

void	here_doc(t_prompt *prompt, t_env *env)
{
	extern int	g_caught;

	if (prompt->type == P_CMD)
	{
		if (!prompt->cmd->limiter)
			return ;
		here_doc0(prompt, prompt->cmd->file, prompt->cmd->limiter, env);
	}
	else
	{
		if (g_caught == 2)
			return ;
		here_doc(prompt->left, env);
		if (g_caught == 2)
			return ;
		here_doc(prompt->right, env);
	}
	if (prompt->subshell)
	{
		if (!prompt->limiter)
			return ;
		here_doc0(prompt, prompt->file, prompt->limiter, env);
	}
}
