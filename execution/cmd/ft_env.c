/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:14 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/11 23:04:44 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_env(t_prompt *prompt, t_env *env)
{
    char *path;

    path = find_path(prompt->cmd->args, env);
    if (!path || !ft_strncmp(path, "env", 4))
    {
        ft_putstr_fd("env: ", 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (127);
    }
    free (path);
    while (env)
    {
        if (env->value && (env->print == ENV_PRINT || env->print == PRINT))
        {
            ft_putstr_fd(env->key, 1);
            ft_putstr_fd(env->value, 1);
            ft_putstr_fd("\n", 1);
        }
        env = env->next;
    }
    return (0);
}
