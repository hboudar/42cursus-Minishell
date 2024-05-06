/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/06 15:51:00 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void set_oldpwd(char *oldpwd, t_env *env)
{
    char *tmp;
    int i;

    i = -1;
    while (env)
    {
        if (!ft_strncmp(env->key, "OLDPWD=", 8))
        {
            tmp = env->value;
            env->value = oldpwd;
            if (!env->value)
            {
                env->value = tmp;
                perror("ft_strjoin in cd");
                break ;
            }
            free(tmp);
            tmp = NULL;
        }
        env = env->next;
    }
    free(oldpwd);
    oldpwd = NULL;
}

void set_pwd(char *pwd, t_env *env)
{
    char *tmp;
    int i;

    i = -1;
    while (env)
    {
        if (!ft_strncmp(env->key, "PWD=", 8))
        {
            tmp = env->value;
            env->value = pwd;
            if (!env->value)
            {
                env->value = tmp;
                perror("ft_strjoin in cd");
                break ;
            }
            free(tmp);
            tmp = NULL;
        }
        env = env->next;
    }
    free(pwd);
    pwd = NULL;
}

//TODO: cd ..
int ft_cd(t_prompt *prompt, t_env *env)
{
    char *oldpwd;
    char *pwd;

    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
    {
        perror("getcwd");
        return (prompt->exit_state);
    }
    if (chdir(prompt->cmd->args[1]) == -1)
    {
        free(oldpwd);
        perror(prompt->cmd->args[1]);
        return (1);
    }
    pwd = getcwd(NULL, 0);
    if (!pwd)
    {
        free(oldpwd);
        perror("getcwd");
        return (prompt->exit_state);
    }
    set_pwd(pwd, env);
    set_oldpwd(oldpwd, env);
    return (0);
}
