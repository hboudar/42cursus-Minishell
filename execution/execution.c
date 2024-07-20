/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:47:57 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/20 15:20:52 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cmd(t_prompt *prompt, t_env **env, t_pid **pids, int mode)
{
	t_env	*tmp_env;

	expand_cmd(prompt, *env);
	tmp_env = *env;
	if (!prompt->cmd)
	{
		ft_putstr_fd("malloc\n", 2);
		return (1);
	}
	if (prompt->cmd && prompt->cmd->args)
		change_underscore(env,
			prompt->cmd->args[ft_tablen(prompt->cmd->args) - 1]);
	else if (prompt->cmd)
		change_underscore(env, "");
	if (!prompt->cmd->args || is_builtin(prompt))
		redirection(prompt, env, prompt->cmd->file);
	else
		none_builtin(prompt, *env, mode, pids);
	return (prompt->exit_state);
}

int	ft_or(t_prompt *prompt, t_env **env, t_pid **pids)
{
	int	fd0;
	int	fd1;

	(1) && (fd0 = 0, fd1 = 1);
	(1) && (fd0 = dup(0), fd1 = dup(1));
	prompt->exit_state = execution(prompt->left, env, pids, 2);
	(1) && (dup2(fd0, 0), dup2(fd1, 1));
	(fd0 != 0) && (close(fd0));
	(fd1 != 1) && (close(fd1));
	if (prompt->exit_state)
		prompt->exit_state = execution(prompt->right, env, pids, 0);
	return (prompt->exit_state);
}

int	ft_and(t_prompt *prompt, t_env **env, t_pid **pids)
{
	int	fd0;
	int	fd1;

	(1) && (fd0 = 0, fd1 = 1);
	(1) && (fd0 = dup(0), fd1 = dup(1));
	prompt->exit_state = execution(prompt->left, env, pids, 2);
	(1) && (dup2(fd0, 0), dup2(fd1, 1));
	(fd0 != 0) && (close(fd0));
	(fd1 != 1) && (close(fd1));
	if (!prompt->exit_state)
		prompt->exit_state = execution(prompt->right, env, pids, 0);
	return (prompt->exit_state);
}

int	execution(t_prompt *prompt, t_env **env, t_pid **pids, int mode)
{
	if (prompt->subshell)
		prompt->exit_state = subshell(prompt, env, NULL, pids);
	else if (prompt->type == P_CMD)
		prompt->exit_state = ft_cmd(prompt, env, pids, mode);
	else if (prompt->type == P_PIPE)
	{
		prompt->exit_state = ft_pipe(prompt->left, env, 'L', pids);
		prompt->exit_state = ft_pipe(prompt->right, env, 'R', pids);
	}
	else if (prompt->type == P_OR)
		prompt->exit_state = ft_or(prompt, env, pids);
	else if (prompt->type == P_AND)
		prompt->exit_state = ft_and(prompt, env, pids);
	return (prompt->exit_state);
}
