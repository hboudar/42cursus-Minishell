/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/04/20 16:58:25 by aoulahra         ###   ########.fr       */
=======
/*   Updated: 2024/04/23 08:54:58 by hboudar          ###   ########.fr       */
>>>>>>> a64b1918a8c4b26a2199b50229ce55654d5dd616
=======
/*   Updated: 2024/04/23 13:08:57 by hboudar          ###   ########.fr       */
>>>>>>> c16e03627442c4373386e6ddc305ea6878482c24
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

<<<<<<< HEAD
<<<<<<< HEAD
=======
int execution(t_prompt *prompt, char *env[])
=======
int one_prompt(t_prompt *prompt, char *env[])
>>>>>>> c16e03627442c4373386e6ddc305ea6878482c24
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
>>>>>>> a64b1918a8c4b26a2199b50229ce55654d5dd616
