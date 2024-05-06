/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/06 15:47:55 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	one_prompt(t_prompt *prompt, t_env *env)
{
	if (prompt->cmd->type == CMD)
	{
		if (is_builtin(prompt))
			return (execute_builtin(prompt, env));
		// return (execute_cmd(prompt));
	}
    else if (prompt->cmd->type == PIPECMD)
    {
        ;
    }
    else if (prompt->cmd->type == HERE_DOC)
    {
        ;
    }
	return (prompt->exit_state);
}

int	execution(t_prompt *prompt, t_env *env)
{
	if (prompt->type == NONE)
		return (one_prompt(prompt, env));
	else if (prompt->type == OR)
	{
		if (!execution(prompt->left, env))
			execution(prompt->right, env);
	}
	else if (prompt->type == AND)
	{
		if (execution(prompt->left, env))
			execution(prompt->right, env);
	}
	return (prompt->exit_state);
}
