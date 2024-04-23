/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/20 16:58:25 by aoulahra         ###   ########.fr       */
=======
/*   Updated: 2024/04/23 08:54:58 by hboudar          ###   ########.fr       */
>>>>>>> a64b1918a8c4b26a2199b50229ce55654d5dd616
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

<<<<<<< HEAD
=======
int execution(t_prompt *prompt, char *env[])
{
    if (1)
        execute_one_cmd(prompt, env);
    else if ("pipe")
        execute_pipe(prompt, env);
}

int main(int ac, char **av, char *env[])
{
    t_prompt prompt;

    
    execution(&prompt, env);
    return (0);
}
>>>>>>> a64b1918a8c4b26a2199b50229ce55654d5dd616
