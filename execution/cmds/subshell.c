/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:35:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/18 12:25:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_redirection(t_file *file, char c)
{
	t_file	*tmp;

	if (c == 'P')
		printf("in prompt : ");
	else if (c == 'L')
		printf("in left : ");
	else if (c == 'R')
		printf("in right : ");
	if (!file)
	{
		printf("no redirection\n");
		return ;
	}
	tmp = file;
	while (tmp)
	{
		if (tmp->type == 1)
			printf("redirection out : %s | ", tmp->data);
		else if (tmp->type == 2)
			printf("redirection out append : %s | ", tmp->data);
		else if (tmp->type == 0)
			printf("redirection in : %s | ", tmp->data);
		else if (tmp->type == 3)
			printf("here_doc : %s | ", tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
}

int	subshell(t_prompt *prompt, t_env **env, int *fd, t_pid **pids)
{
	pid_t	pid;

	prompt->subshell = 0;
	print_redirection(prompt->file, 'P');
	print_redirection(prompt->left->cmd->file, 'L');
	print_redirection(prompt->right->cmd->file, 'R');
	exit(0);
	setup_signal_handlers(sig_handler_child, sig_handler_child);
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		(fd) && (dup2(fd[1], 1), close(fd[0]), close(fd[1]));
		none_redirection(prompt, *env, prompt->file);
		prompt->exit_state = prep_execution(prompt, env, 1);
		printf("{subshell :%d}\n", prompt->exit_state);
		exit(prompt->exit_state);
	}
	else
	{
		ignore_signals();
		pid_addback(pids, new_pid(pid));
		(fd) && (dup2(fd[0], 0), close(fd[0]), close(fd[1]));
	}
	return (prompt->exit_state);
}
