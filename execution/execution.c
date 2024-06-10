/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/10 06:28:43 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_cmd(t_prompt *prompt, t_env **env)
{
	// printf("{ft_cmd}\n");
	expand_cmd(prompt, *env);
	if (!prompt->cmd)
	{
		perror("malloc");
		return (1);
	}
    if (!prompt->cmd->args || is_builtin(prompt))
	{
        redirection(prompt, env);
        return (prompt->exit_state);
    }
	return (execute_nonebuiltin(prompt, *env));
}

int	ft_or(t_prompt *prompt, t_env **env, int fd_in)
{
	// printf("{ft_or}");
	prompt->exit_state = execution(prompt->left, env, fd_in);
	if (prompt->exit_state)
		prompt->exit_state = execution(prompt->right, env, fd_in);
	return (prompt->exit_state);
}

int ft_and(t_prompt *prompt, t_env **env, int fd_in)
{
    // printf("{ft_and}");
    prompt->exit_state = execution(prompt->left, env, fd_in);
    if (!prompt->exit_state)
        prompt->exit_state = execution(prompt->right, env, fd_in);
    return (prompt->exit_state);
}

int	execution(t_prompt *prompt, t_env **env, int std_in)
{
	// printf("{execution}");
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
