/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/09 19:57:07 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
    }
    exit(0);
}

void	here_doc(t_prompt *p, t_file *file, t_limiter *lim)
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
		file->data = ft_strdup("/tmp/.doc");
	}
}

void	do_files(t_prompt *prompt)
{
	if (prompt->subshell)
	{
		here_doc(prompt, prompt->file, prompt->limiter);
		if (prompt->exit_state != 0)
			return ;
	}
	if (prompt->type == P_CMD)
	{
		her_doc(prompt, prompt->cmd->file, prompt->cmd->limiter);
		if (prompt->exit_state != 0)
			return ;
	}
	else
	{
		do_files(prompt->left);
		if (prompt->exit_state != 0)
			return ;
		do_files(prompt->right);
	}
}

int	execution(t_prompt *prompt, t_env **env, int std_in)
{
	printf("execution\n");
	if (prompt->subshell)
		return (subshell(prompt, env));
	else if (prompt->type == P_CMD)
		prompt->exit_state = ft_cmd(prompt, env);
	else if (prompt->type == P_PIPE)
		prompt->exit_state = ft_pipe(prompt, env, std_in);
	else if (prompt->type == P_OR)
		prompt->exit_state = ft_or(prompt, env, std_in);
	else if (prompt->type == P_AND)
		prompt->exit_state = ft_and(prompt, env, std_in);
	return (prompt->exit_state);
}
