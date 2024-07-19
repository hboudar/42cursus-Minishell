/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:07:10 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/19 16:07:13 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->print != NO_PRINT)
			i++;
		env = env->next;
	}
	return (i);
}

char	**free_envp(char **envp)
{
	int	i;

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

char	**env_to_envp(t_env *tmp)
{
	char	**envp;
	int		i;

	i = len_env(tmp);
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (perror("malloc function"), NULL);
	i = -1;
	while (tmp)
	{
		if (tmp->print != NO_PRINT)
		{
			envp[++i] = ft_strjoin(tmp->key, tmp->value);
			if (envp[i] == NULL)
			{
				perror("ft_strjoin failed");
				return (free_envp(envp));
			}
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
