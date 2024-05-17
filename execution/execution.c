/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/17 15:37:04 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_cmd(t_prompt *prompt, t_env *env)
{
	if (prompt->cmd->args == NULL)
		return (no_cmd(prompt));
	else if (is_builtin(prompt))
		return (execute_builtin(prompt, env));
	return (execute_nonebuiltin(prompt, env));
	return (0);
}

int ft_pipe(t_prompt *prompt, t_env *env)
{
	if (prompt->type == P_CMD)
		return (ft_cmd(prompt, env));
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
	return (0);
}

int	execution(t_prompt *prompt, t_env *env)
{
	if (prompt->type == P_CMD)
		return (ft_cmd(prompt, env));
	else if (prompt->type == P_PIPE)
		return (ft_pipe(prompt, env));
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
	return (0);
}
