/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/13 23:46:21 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_cmd(t_prompt *prompt, t_env **env)
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
	return (execute_nonebuiltin(prompt, *env, 0));
}

int	ft_or(t_prompt *prompt, t_env **env)
{
	prompt->exit_state = execution(prompt->left, env);
	if (prompt->exit_state)
		prompt->exit_state = execution(prompt->right, env);
	return (prompt->exit_state);
}

int ft_and(t_prompt *prompt, t_env **env)
{
    prompt->exit_state = execution(prompt->left, env);
    if (!prompt->exit_state)
        prompt->exit_state = execution(prompt->right, env);
    return (prompt->exit_state);
}

int	execution(t_prompt *prompt, t_env **env)
{
	if (prompt->subshell)
		return (subshell(prompt, env, NULL));
	else if (prompt->type == P_CMD)
		prompt->exit_state = ft_cmd(prompt, env);  
	else if (prompt->type == P_PIPE)
	{
		prompt->exit_state = ft_pipe(prompt->left, env, 'L');
		prompt->exit_state = ft_pipe(prompt->right, env, 'R');
	}
	else if (prompt->type == P_OR)
		prompt->exit_state = ft_or(prompt, env);
	else if (prompt->type == P_AND)
		prompt->exit_state = ft_and(prompt, env);
	return (prompt->exit_state);
}
