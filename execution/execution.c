/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/06 16:42:00 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_cmd(t_prompt *prompt)
{
	(void)prompt;
	return (0);
}

int	one_cmd(t_prompt *prompt, t_env *env)
{
	if (is_builtin(prompt))
		return (execute_builtin(prompt, env));
	return (execute_cmd(prompt));
}

int	execution(t_prompt *prompt, t_env *env)
{
	if (prompt->type == P_CMD)
		return (one_cmd(prompt, env));
	// else if (prompt->type == P_PIPE)
	// 	pipe_execution(prompt, env);
	// else if (prompt->type == P_OR)
	// {
	// 	if (!execution(prompt->left, env))
	// 		execution(prompt->right, env);
	// }
	// else if (prompt->type == P_AND)
	// {
	// 	if (execution(prompt->left, env))
	// 		execution(prompt->right, env);
	// }
	return (prompt->exit_state);
}
