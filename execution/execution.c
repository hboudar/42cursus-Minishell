/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/30 20:01:41 by hboudar          ###   ########.fr       */
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

int	execution(t_prompt *prompt, t_env **env)
{
	if (prompt->type == P_CMD)
		return (ft_cmd(prompt, env));
	else if (prompt->type == P_PIPE)
		return (ft_pipe(prompt, env));
	else if (prompt->type == P_OR)
		return (ft_or(prompt, env));
	else if (prompt->type == P_AND)
		return (ft_and(prompt, env));
	return (0);
}
