/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/01 00:08:26 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_cmd(t_prompt *prompt, t_env **env)
{
    if (!prompt->cmd->args)
		return (no_cmd(prompt, env));
	else if (is_builtin(prompt))
		return (execute_builtin(prompt, env));
	return (execute_nonebuiltin(prompt, *env));
}

int	execution(t_prompt *prompt, t_env **env, int std_out, int std_in)
{
	if (prompt->type == P_CMD)
		prompt->exit_state = ft_cmd(prompt, env);
	else if (prompt->type == P_PIPE)
		prompt->exit_state = ft_pipe(prompt, env);
	else if (prompt->type == P_OR)
		prompt->exit_state = ft_or(prompt, env);
	else if (prompt->type == P_AND)
		prompt->exit_state = ft_and(prompt, env);
	return (prompt->exit_state);
}

//in execution include expanding
//in here_doc include expanding