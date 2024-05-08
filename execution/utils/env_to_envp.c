/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:46:44 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/08 10:41:39 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char   **free_envp(char **envp)
{
    int i;

    i = 0;
    if (!envp)
        return (NULL);
    while (envp[i])
    {
        free(envp[i]);
        envp[i] = NULL;
        i++;
    }
    free(envp);
    envp = NULL;
    return (NULL);
}

char	**env_to_envp(t_env *env)
{
    char	**envp;
    t_env    *tmp;
    int		i;

    (1) && (i = 0, tmp = env);
    while (tmp)
        (1) && (i++, tmp = tmp->next);
    envp = malloc(sizeof(char *) * (i + 1));
    if (!envp)
        return (NULL);
    (1) && (i = -1, tmp = env);
    while (tmp)
    {
        envp[++i] = ft_strjoin(tmp->key, tmp->value);
        if (!envp[i])
        {
            perror("ft_strjoin failed");
            return (free_envp(envp));
        }
        tmp = tmp->next;
    }
    envp[i] = NULL;
    return (envp);
}
