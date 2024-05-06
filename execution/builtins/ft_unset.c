/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:33 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/06 15:51:22 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

bool    is_valid_name(const char *name)
{
    int i;

    if (!ft_isalpha(name[0]) && name[0] != '_')
        return false;
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) || name[i] != '_')
            return false;
        i++;
    }
    return true;
}

void    ft_unsetenv(t_prompt *prompt, const char *name, t_env *env)
{
    t_env *tmp;
    t_env *prev;

    tmp = env;
    prev = NULL;
    while (tmp)
    {
        if (!ft_strncmp(tmp->key, name, ft_strlen(name)))
        {
            (1) && (free(tmp->key), tmp->key = NULL);
            (1) && (free(tmp->value), tmp->value = NULL);
            if (prev)
                prev->next = tmp->next;
            else
                env = tmp->next;
            (1) && (free(tmp), tmp = NULL);
            return ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    prompt->exit_state = 0;
}

int ft_unset(t_prompt *prompt, t_env *env)
{
    int i;

    i = 1;
    while (prompt->cmd->args[i] != NULL)
    {
        if (is_valid_name(prompt->cmd->args[i]))
            ft_unsetenv(prompt, prompt->cmd->args[i], env);
        else
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(prompt->cmd->args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            // prompt->exit_state = 1;
        }
        i++;
    }   
    return (prompt->exit_state);
}
