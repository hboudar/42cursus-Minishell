/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 23:50:56 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/20 06:58:58 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	non_outredirect(t_file *file, int *fd1)
{
	if (file->type == 1)
		*fd1 = open(file->data, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (file->type == 2)
		*fd1 = open(file->data, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (*fd1 == -1)
	{
		printf("Error: %s: %s\n", file->data, strerror(errno));
		return (0);
	}
	if (dup2(*fd1, 1) == -1)
	{
		(*fd1 != 1) && (close(*fd1));
		perror("dup2 in out");
		return (0);
	}
	return (1);
}

static int	non_inredirect(t_file *file, int *fd0)
{
	(*fd0 != 0) && (close(*fd0));
	if (!file->type)
		*fd0 = open(file->data, O_RDONLY);
	else if (file->type == 3)
	{
		dup2(file->fd, 0);
		close(file->fd);
		return (1);
	}
	if (*fd0 == -1)
	{
		perror(file->data);
		return (0);
	}
	if (dup2(*fd0, 0) == -1)
	{
		(*fd0 != 0) && (close(*fd0));
		perror("dup2 in in");
		return (0);
	}
	return (1);
}

void	none_redirection(t_prompt *prompt, t_env *env, t_file *file)
{
	int	fd0;
	int	fd1;

	(1) && (fd0 = 0, fd1 = 1, prompt->exit_state = 0);
	while (file != NULL)
	{
		expand_file(file, env);
		if (file->data && !file->data[0] && !file->quotes)
		{
			(fd0 != 0) && (close(fd0));
			(fd1 != 1) && (close(fd1));
			printf("minishell: ambiguous redirect\n");
			exit(1);
		}
		if ((!file->type || file->type == 3) && !non_inredirect(file, &fd0))
			exit(1);
		else if ((file->type == 1 || file->type == 2)
			&& !non_outredirect(file, &fd1))
			exit(1);
		file = file->next;
	}
}
