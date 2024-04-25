/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/25 16:49:54 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	one_prompt(t_prompt *prompt)
{
	if (prompt->cmd->type == CMD)
	{
		if (is_builtin(prompt))
			return (execute_builtin(prompt));
		else
			return (execute_cmd(prompt));
	}
    else if (prompt->cmd->type == PIPECMD)
    {
        ;
    }
    else if (prompt->cmd->type == HERE_DOC)
    {
        ;
    }
}

int	execution(t_prompt *prompt)
{
	if (prompt->type == NONE)
		return (one_prompt(prompt));
	else if (prompt->type == OR)
	{
		if (!execution(prompt->left))
			execution(prompt->right);
	}
	else if (prompt->type == AND)
	{
		if (execution(prompt->left))
			execution(prompt->right);
	}
}
