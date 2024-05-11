/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/10 18:57:48 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static int is_valid_name(const char *name)
{
    int i;

    if (!ft_isalpha(name[0]) && name[0] != '_')
        return (0);
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) || name[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

void    sort_env(t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (env)
    {
        ;
    }
}

static void export_only(t_prompt *prompt, t_env *env)
{
    while (env)
    {
        if (env->value)
            printf("declare -x %s\"%s\"\n", env->key, env->value);
        else
            printf("declare -x %s\n", env->key);
        env = env->next;
    }
    prompt->exit_state = 0;
}

static void    add_env(const char *key, const char *value, t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return ;
        }
        tmp = tmp->next;
    }
    tmp = env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = malloc(sizeof(t_env));
    if (!tmp->next)
    {
        perror("malloc in export");
        return ;
    }
    tmp->next->key = ft_strdup(key);
    tmp->next->value = ft_strdup(value);
    tmp->next->next = NULL;
}

int ft_export(t_prompt *prompt, t_env *env)
{
    if (prompt->cmd->args[1] == NULL)
    {
        export_only(prompt, env);
        return (0);
    }
    else if (!is_valid_name(prompt->cmd->args[1]))
    {
        printf("minishell: export: `%s': not a valid identifier\n", prompt->cmd->args[1]);
        prompt->exit_state = 1;
        return (1);
    }
    else
    {
        if (prompt->cmd->args[2] == NULL)
            add_env(prompt->cmd->args[1], "", env);
        else
            add_env(prompt->cmd->args[1], prompt->cmd->args[2], env);
    }
    return (0);
}
