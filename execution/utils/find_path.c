/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 09:07:24 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/23 11:45:44 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*free_array(char **array)
{
	int	i;

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

char	*get_env(char *key, t_env *env, int mode)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, 5))
		{
			if (mode && env->print == NO_PRINT)
				return (NULL);
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

static char	*ft_pathcmd(char *cmd, char **path, int i)
{
	char	*tmp2;
	char	*tmp;

	tmp = ft_strjoin(path[i], "/");
	if (!tmp)
	{
		perror("ft_strjoin failed");
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

	i = -1;
	if (ft_strchr(cmd[0], '/'))
		return (cmd[0]);
	else if (!get_env("PATH=", env, 1))
		return (NULL);
	path = ft_split(get_env("PATH=", env, 1), ':');
	while (path[++i])
	{
		tmp = ft_pathcmd(cmd[0], path, i);
		if (!access(tmp, F_OK))
		{
			free_array(path);
			return (tmp);
		}
		free(tmp);
	}
	return (free_array(path));
}
