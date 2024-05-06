/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:10 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/06 15:31:12 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

//when {echo - args} : "-" is not displayed

void echo_without_newline(t_prompt *prompt)
{
    int i;

    i = 1;
    while (prompt->cmd->args[i])
    {
        ft_putstr_fd(prompt->cmd->args[i], 1);
        if (prompt->cmd->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
}

void echo_with_newline(t_prompt *prompt)
{
    int i;

    i = 1;
    while (prompt->cmd->args[i])
    {
        ft_putstr_fd(prompt->cmd->args[i], 1);
        if (prompt->cmd->args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    ft_putstr_fd("\n", 1);
}

int ft_echo(t_prompt *prompt, t_env *env)
{
    int i;

    if (prompt->cmd->args[1])
    {
        if (!ft_strncmp(prompt->cmd->args[1], "-n", 3))
            echo_without_newline(prompt);
        else
            echo_with_newline(prompt);
    } 
    return (0);
}
