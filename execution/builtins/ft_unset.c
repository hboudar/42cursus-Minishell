/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:33 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/28 20:48:10 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

bool    is_valid_name(const char *name)
{
    int i;

    if (!ft_isalpha(name[0]) && name[0] != '_')
        return false;
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) || name[i] != '_')
            return false;
        i++;
    }
    return true;
}

int ft_unset(t_prompt *prompt, char *env[])
{
    int i;
    int return_value;

    (1) && (i = 1, return_value = 0);
    while (prompt->cmd->args[i])
    {
        if (is_valid_name(prompt->cmd->args[i]))
            ft_unsetenv(prompt->cmd->args[i], env);
        else
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(prompt->cmd->args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            return_value = 1;
        }
    }   
    return (return_value);
}
