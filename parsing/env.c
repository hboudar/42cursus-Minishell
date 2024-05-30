/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:10:07 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/30 16:56:55 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_env(char **envp)
{
	if (envp && !envp[0])
	{
		printf("Error: empty enviroment\n");
		return (1);
	}
	return (0);
}

void	ft_shell_lvl(t_env *env)
{
	char	*str;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "SHLVL", 5))
		{
			str = ft_itoa(ft_atoi(tmp->value) + 1);
			if (!str)
				return (perror("E: ft_itoa in ft_shell_lvl"));
			if (ft_strncmp(tmp->value, "999", 3) == 0)
			{
				free(str);
				free(tmp->value);
				return ;
			}
			free(tmp->value);
			tmp->value = str;
			break ;
		}
		tmp = tmp->next;
	}
}

char	*get_env_value(char **tmp, t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->key, *tmp, ft_strlen(tmp_env->key) - 1)
			&& ft_strlen(tmp_env->key) == ft_strlen(*tmp) + 1)
				return (ft_strdup(tmp_env->value));
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

void	expand_env(t_token **token, t_token *to_expand, t_env *env)
{
	int		i;
	char	**tmp;
	char	*value;

	tmp = to_expand->expand;
	i = 0;
	while (*tmp)
	{
		i++;
		value = get_env_value(tmp, env);
		free(*tmp);
		if (!value)
			*tmp = NULL;
		else
			*tmp = value;
		tmp++;
	}
	if (is_empty(to_expand->expand, i) == i)
		remove_token(token, to_expand);
	else
		expand_data(to_expand, i, 0, 0);
}

void	expand_tokens(t_token **token, t_env *env)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->expand)
			expand_env(token, tmp, env);
		tmp = tmp->next;
	}
}
