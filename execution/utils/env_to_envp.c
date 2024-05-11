/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:46:44 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/11 16:48:36 by hboudar          ###   ########.fr       */
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

char	**env_to_envp(t_env *tmp, t_env *tmp1)
{
    char	**envp;
    int		i;

    i = -1;
    while (tmp1 && ++i >= 0)
        tmp1 = tmp1->next;
    envp = malloc(sizeof(char *) * (i + 1));
    if (!envp)
        return (perror("malloc function"), NULL);
    i = -1;
    while (tmp)
    {
        envp[++i] = ft_strjoin(tmp->key, tmp->value);
        if (envp[i] == NULL)
        {
            perror("ft_strjoin failed");
            return (free_envp(envp));
        }
        tmp = tmp->next;
    }
    envp[i] = NULL;
    return (envp);
}
