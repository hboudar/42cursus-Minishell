/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:14 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/30 07:36:02 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_env(t_prompt *prompt, char *env[])
{
    int i;

    i = 0;
    while (env && env[i])
    {
        ft_putstr_fd(env[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
        prompt->exit_state = 0;
    }
    return (prompt->exit_state);
}
