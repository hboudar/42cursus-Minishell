/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 08:54:28 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_cmd(t_prompt *prompt, t_env **env, t_pid **pids)
{
	expand_cmd(prompt, *env);
	if (!prompt->cmd)
	{
		perror("malloc");
		return (1);
	}
	if (!prompt->cmd->args || is_builtin(prompt))
	{
		redirection(prompt, env, prompt->cmd->file);
		return (prompt->exit_state);
	}
	return (exec_nonebuiltin(prompt, *env, 0, pids));
}

int	ft_or(t_prompt *prompt, t_env **env, t_pid **pids)
{
	prompt->exit_state = execution(prompt->left, env, pids);
	if (prompt->exit_state)
		prompt->exit_state = execution(prompt->right, env, pids);
	return (prompt->exit_state);
}

int	ft_and(t_prompt *prompt, t_env **env, t_pid **pids)
{
	prompt->exit_state = execution(prompt->left, env, pids);
	if (!prompt->exit_state)
		prompt->exit_state = execution(prompt->right, env, pids);
	return (prompt->exit_state);
}

int	execution(t_prompt *prompt, t_env **env, t_pid **pids)
{
	if (prompt->subshell)
		prompt->exit_state = subshell(prompt, env, NULL, pids);
	else if (prompt->type == P_CMD)
		prompt->exit_state = ft_cmd(prompt, env, pids);
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
