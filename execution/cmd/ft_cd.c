/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/22 23:32:48 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void set_oldpwd(char *oldpwd, t_env *env)
{
    while (env)
    {
        if (!ft_strncmp(env->key, "OLDPWD", 7))
        {
            if (!env->value)
            {
                env->value = oldpwd;
                free(env->key);
                env->key = ft_strdup("OLDPWD=");
                if (!env->key)
                    return ;
                env->print = PRINT;
            }
            else
            {
                free(env->value);
                env->value = NULL;
                env->value = oldpwd;
                env->print = PRINT;
            }
        }
        env = env->next;
    }
}

void set_pwd(char *pwd, t_env *env)
{
    while (env)
    {
        if (!ft_strncmp(env->key, "PWD=", 8))
        {
            free(env->value);
            env->value = NULL;
            env->value = pwd;
        }
        env = env->next;
    }
}

int ft_cd(t_prompt *prompt, t_env *env)
{
    char *oldpwd;
    char *pwd;

    if (prompt->cmd->args[1] == NULL)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        return (1);
    }
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        return (perror("getcwd"), 1);
    if (chdir(prompt->cmd->args[1]) == -1)
    {
        free(oldpwd);
        perror(prompt->cmd->args[1]);
        return (1);
    }
    pwd = getcwd(NULL, 0);
    if (!pwd)
        return (free(oldpwd), perror("getcwd"), 1);
    set_pwd(pwd, env);
    set_oldpwd(oldpwd, env);
    return (0);
}
