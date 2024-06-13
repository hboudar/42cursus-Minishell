/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/13 02:28:01 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void    add_path(char *path, char *key, t_env *env)
{
    while (env->next)
        env = env->next;
    env->next = malloc(sizeof(t_env));
    if (!env->next)
        return ;
    env->next->key = ft_strdup(key);
    if (!env->next->key)
        return ;
    env->next->value = ft_strdup(path);
    if (!env->next->value)
        return ;
    env->next->print = PRINT;
    env->next->next = NULL;
}

void set_oldpwd(char *oldpwd, t_env *tmp_env, t_env *env)
{
    while (tmp_env)
    {
        if (!ft_strncmp(tmp_env->key, "OLDPWD", 6))
        {
            if (!tmp_env->value)
            {
                free(tmp_env->key);
                tmp_env->key = ft_strdup("OLDPWD=");
                if (!tmp_env->key)
                    return ;
            }
            else
            {
                free(tmp_env->value);
                tmp_env->value = NULL;
            }
            tmp_env->value = ft_strdup(oldpwd);
            tmp_env->print = PRINT;
            return ;
        }
        tmp_env = tmp_env->next;
    }
    if (!tmp_env)
        add_path(oldpwd, "OLDPWD=", env);
}

void set_pwd(char *pwd, t_env *tmp_env, t_env *env)
{
    while (tmp_env)
    {
        if (!ft_strncmp(tmp_env->key, "PWD=", 8))
        {
            if (tmp_env->value != NULL)
            {
                free(tmp_env->value);
                tmp_env->value = NULL;
            }
            tmp_env->value = ft_strdup(pwd);
            return ;
        }
        tmp_env = tmp_env->next;
    }
    if (!tmp_env)
        add_path(pwd, "PWD=", env);
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
    char *oldpwd = NULL;
    char *pwd;

    if (prompt->cmd->args[1] == NULL)
    {
        ft_putstr_fd("cd: NO arguments\n", 2);
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
    (1) && (set_pwd(pwd, env, env), free(pwd), pwd = NULL);
    (1) && (set_oldpwd(oldpwd, env, env), free(oldpwd), oldpwd = NULL);
    return (0);
}
