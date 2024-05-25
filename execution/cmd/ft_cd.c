/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/25 18:10:57 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void set_oldpwd(char *oldpwd, t_env *env)
{
    while (env)
    {
        if (!ft_strncmp(env->key, "OLDPWD", 6))
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

char *ft_getpwd(char *arg, t_env *env, int mode)
{
    char *pwd;
    char *tmp;

    pwd = getcwd(NULL, 0);
    if (pwd != NULL)
        return (pwd);
    while (env)
    {
        if (!ft_strncmp(env->key, "PWD=", 5))
            break ;
        env = env->next;
    }
    if (!env)
        return (NULL);
    if (!mode)
        return (ft_strdup(env->value));
    tmp = ft_strjoin(env->value, "/");
    if (!tmp)
        return (NULL);
    pwd = ft_strjoin(tmp, arg);
    free(tmp);
    if (!pwd)
        return (NULL);
    return (pwd);
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
    oldpwd = ft_getpwd(prompt->cmd->args[1], env, 0);
    if (!oldpwd)
        perror("Error in getcwd {oldpwd}");
    if (chdir(prompt->cmd->args[1]) == -1)
    {
        free(oldpwd);
        perror("Error in cd {chdir}");
        return (1);
    }
    pwd = ft_getpwd(prompt->cmd->args[1], env, 1);
    if (!pwd)
        perror("Error in ft_getcwd {pwd}");
    set_pwd(pwd, env);
    set_oldpwd(oldpwd, env);
    return (0);
}
