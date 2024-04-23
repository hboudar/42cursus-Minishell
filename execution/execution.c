/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/23 08:54:58 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
