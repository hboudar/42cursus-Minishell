/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/23 15:12:22 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int one_prompt(t_prompt *prompt, char *env[])
{
    if (prompt->cmd->type == CMD)
    {
    }
}

int execution(t_prompt *prompt, char *env[])
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
}
