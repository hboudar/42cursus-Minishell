/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:29 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/25 18:15:48 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static char *ft_getcwd(t_env *env)
{
    char *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd)
        return (pwd);
    while (env)
    {
        if (!ft_strncmp(env->key, "PWD=", 5))
            break ;
        env = env->next;
    }
    if (!env)
        return (NULL);
    return (env->value);
}

int ft_pwd(t_prompt *prompt, t_env *env)
{
    char *pwd;
    
    pwd = ft_getcwd(env);
    if (pwd == NULL)
    {
        perror("pwd failed");
        prompt->exit_state = 1;
        return (1);
    }
    printf("%s\n", pwd);
    prompt->exit_state = 0;
    return (0);
}
