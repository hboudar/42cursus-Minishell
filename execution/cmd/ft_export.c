/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/12 00:54:55 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int is_valid_name(const char *name)
{
    int i;

    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    else if (ft_strchr(name, '='))
        return (1);
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static int export_only(t_env *env)
{
    while (env)
    {
        if (env->print == PRINT || env->print == EXP_PRINT)
        {
            if (env->value)
                printf("declare -x %s\"%s\"\n", env->key, env->value);
            else
                printf("declare -x %s\n", env->key);
        }
        env = env->next;
    }
    return (0);
}

static void    add_env_1(const char *str, t_env *env)
{
    while (env)
    {
        if (!ft_strncmp(env->key, str, ft_strlen(str)))
            return ;
        if (!env->next)
            break ;
        env = env->next;
    }
    env->next = malloc(sizeof(t_env));
    if (!env->next)
    {
        perror("malloc in add_env_2 failed");
        return ;
    }
    env->next->key = ft_strdup(str);
    if (!env->next->key)
    {
        free(env->next);
        perror("ft_strdup in add_env_2 failed");
        return ;
    }
    env->next->value = NULL;
    env->next->next = NULL;
    env->next->print = EXP_PRINT;
}

static void    add_env_2(const char *str, t_env *env)
{
    while (env->next)
        env = env->next;
    env->next = malloc(sizeof(t_env));
    if (!env->next)
        return (perror("malloc in add_env_1 failed"));
    env->next->key = ft_substr(str, 0, (size_t)(ft_strchr(str, '=') - str));
    if (!env->next->key)
        return (free(env->next), perror("ft_substr in add_env_1 failed"));
    env->next->value = ft_strdup(ft_strchr(str, '='));
    if (!env->next->value)
        return (free(env->next->key), free(env->next), perror("ft_strdup in add_env_1 failed"));
    env->next->next = NULL;
    env->next->print = PRINT;
}

static void   add_env_3(const char *str, t_env *env)
{
    char    *tmp;

    while (env)
    {
        if (!ft_strncmp(env->key, str, ft_strlen(str)) && env->value)
        {
            tmp = ft_strjoin(env->value, ft_strchr(str, '=') + 1);
            if (!tmp)
                return (perror("ft_strjoin in add_env_3 failed"));
            free(env->value);
            env->value = tmp;
            return ;
        }
        else if (!ft_strncmp(env->key, str, ft_strlen(str)) && !env->value)
        {
            env->value = ft_strdup(ft_strchr(str, '='));
            if (!env->value)
                return (perror("ft_strdup in add_env_3 failed"));
            return ;
        }
        env = env->next;
    }
}

int ft_export(t_prompt *prompt, t_env *env)
{
    int i;

    if (prompt->cmd->args[1] == NULL)
        return (export_only(env));
    i = 0;
    while (prompt->cmd->args[++i])
    {
        if (!is_valid_name(prompt->cmd->args[i]))
        {
            printf("export: `%s': not a valid identifier\n", prompt->cmd->args[i]);
            prompt->exit_state = 1;
        }
        else if (ft_strchr(prompt->cmd->args[i], '+'))
            add_env_3(prompt->cmd->args[i], env);
        else if (ft_strchr(prompt->cmd->args[i], '='))
            add_env_2(prompt->cmd->args[i], env);
        else
            add_env_1(prompt->cmd->args[i], env);
    }
    return (0);
}
