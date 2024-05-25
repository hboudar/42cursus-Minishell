/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 08:46:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/25 15:35:44 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_builtin(t_prompt *prompt)
{
	return ((!ft_strncmp(prompt->cmd->args[0], "echo", 5)
			|| !ft_strncmp(prompt->cmd->args[0], "cd", 3)
			|| !ft_strncmp(prompt->cmd->args[0], "pwd", 4)
			|| !ft_strncmp(prompt->cmd->args[0], "export", 7)
			|| !ft_strncmp(prompt->cmd->args[0], "unset", 6)
			|| !ft_strncmp(prompt->cmd->args[0], "env", 4)
			|| !ft_strncmp(prompt->cmd->args[0], "exit", 5)));
}

static int  ft_outredirect(t_prompt *prompt, int *fd1)
{
    if (prompt->cmd->file->type == 1)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (prompt->cmd->file->type == 2)
        *fd1 = open(prompt->cmd->file->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (*fd1 == -1)
    {
        printf("Error: %s: %s\n", prompt->cmd->file->next->data, strerror(errno));
        return (0);
    }
    if (dup2(*fd1, 1) == -1)
    {
        close(*fd1);
        perror("dup2");
        return (0);
    }
    return (1);
}

static int	ft_inredirect(t_prompt *prompt, int *fd0)
{
    if (*fd0 != 0)
        close(*fd0);
    *fd0 = open(prompt->cmd->file->data, O_RDONLY);
    if (*fd0 == -1)
    {
        perror(prompt->cmd->file->data);
        return (0);
    }
    if (dup2(*fd0, 0) == -1)
    {
        close(*fd0);
        perror("dup2");
        return (0);
    }
    return (1);
}

static int	ft_builtin(t_prompt *prompt, t_env **env)
{
	if (!ft_strncmp(prompt->cmd->args[0], "echo", 5))//done
		return (ft_echo(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "cd", 3))//done
		return (ft_cd(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "pwd", 4))//done
		return (ft_pwd(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "export", 7))//done
		return (ft_export(prompt, *env));
	else if (!ft_strncmp(prompt->cmd->args[0], "unset", 6))//done
		return (ft_unset(prompt, env));
	else if (!ft_strncmp(prompt->cmd->args[0], "env", 4))//done
		return (ft_env(prompt, *env));
	return (ft_exit(prompt));
}

int	execute_builtin(t_prompt *prompt, t_env **env)
{
	int	fd0;
	int	fd1;

	fd0 = 0;
	while (prompt->cmd->file)
    {
        if (!prompt->cmd->file->type && !ft_inredirect(prompt, &fd0))
            exit(1);
        else if (prompt->cmd->file->type && !ft_outredirect(prompt, &fd1))
            exit(1);
        prompt->cmd->file = prompt->cmd->file->next;
    }
	prompt->exit_state = ft_builtin(prompt, env);
	if (fd0 != 0)
		close(fd0);
	if (fd1 != 1)
		close(fd1);
	return (prompt->exit_state);
}
