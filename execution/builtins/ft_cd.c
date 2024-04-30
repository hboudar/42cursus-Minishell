/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/30 16:14:22 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void set_oldpwd(char *env[], char *oldpwd)
{
    char *tmp;
    int i;

    i = -1;
    while (env && env[++i])
    {
        if (!ft_strncmp(env[i], "OLDPWD=", 7))
        {
            tmp = env[i];
            env[i] = ft_strjoin("OLDPWD=", oldpwd);
            if (!env[i])
            {
                env[i] = tmp;
                perror("ft_strjoin in cd");
                break ;
            }
            free(tmp);
            tmp = NULL;
        }
    }
    free(oldpwd);
    oldpwd = NULL;
}

void set_pwd(char *env[], char *pwd)
{
    char *tmp;
    int i;

    i = -1;
    while (env && env[++i])
    {
        if (!ft_strncmp(env[i], "PWD=", 4))
        {
            tmp = env[i];
            env[i] = ft_strjoin("PWD=", pwd);
            if (!env[i])
            {
                env[i] = tmp;
                perror("ft_strjoin in cd");
                break ;
            }
            free(tmp);
            tmp = NULL;
        }
    }
    free(pwd);
    pwd = NULL;
}

//TODO: cd ..
int ft_cd(t_prompt *prompt, char *env[])
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
    set_pwd(env, pwd);
    set_oldpwd(env, oldpwd);
    return (0);
}
