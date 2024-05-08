/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:07:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/08 11:22:53 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static char    *free_array(char **array)
{
    int i;

    i = -1;
    if (array == NULL)
        return (NULL);
    while (array[++i])
    {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
    array = NULL;
    return (NULL);
}

static char    *get_env_value(char *key, t_env *env)
{
    t_env   *tmp;

    tmp = env;
    while (tmp && tmp->key)
    {
        if (!ft_strncmp(tmp->key, key, 5))
            break ;
        tmp = tmp->next;
    }
    return (tmp->value);
}

static char    *ft_pathcmd(char *cmd, char **path, int i)
{
    char    *tmp;
    char    *tmp2;

    tmp = ft_strjoin(path[i], "/");
    if (!tmp)
    {
        perror("ft_strjoi failed");
        return (free_array(path));
    }
    tmp2 = ft_strjoin(tmp, cmd);
    free(tmp);
    if (!tmp2)
    {
        perror("ft_strjoin failed");
        return (free_array(path));
    }
    return (tmp2);
}

char	*find_path(char **cmd, t_env *env)
{
    char	**path;
    char	*tmp;
    int		i;

    (1) && (path = ft_split(get_env_value("PATH", env), ':'), i = -1);
    if (!path)
        return (perror("ft_split failed"), NULL);
    while (path[++i])
    {
        tmp = ft_pathcmd(cmd[0], path, i);
        if (!tmp)
            return (NULL);
        if (!access(tmp, F_OK))
        {
            free_array(path);
            return (tmp);
        }
        free(tmp);
    }
    free_array(path);
    return (cmd[0]);
}
