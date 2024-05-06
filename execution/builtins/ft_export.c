/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:22 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/02 17:23:02 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void export_only(t_prompt *prompt, t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (tmp->value)
            printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
        else
            printf("declare -x %s\n", tmp->key);
        tmp = tmp->next;
    }
    prompt->exit_state = 0;
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
