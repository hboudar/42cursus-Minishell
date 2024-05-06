/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/06 16:28:44 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	one_cmd(t_prompt *prompt, t_env *env)
{
	if (is_builtin(prompt))
		return (execute_builtin(prompt, env));
	return (execute_cmd(prompt));
}

int	execution(t_prompt *prompt, t_env *env)
{
	if (prompt->type == CMD)
		return (one_cmd(prompt, env));
	else if (prompt->type == PIPE)
		return (pipe_cmds(prompt, env));
	// else if (prompt->type == OR)
	// {
	// 	if (!execution(prompt->left, env))
	// 		execution(prompt->right, env);
	// }
	// else if (prompt->type == AND)
	// {
	// 	if (execution(prompt->left, env))
	// 		execution(prompt->right, env);
	// }
	return (prompt->exit_state);
}
