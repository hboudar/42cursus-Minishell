/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:10:07 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/02 10:24:51 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_getenv(char *name, t_env *env)
{
	char	*data;

	data = NULL;
	while (*name && *name != '$')
		name++;
	name++;
	while (env)
	{
		if (ft_strncmp(env->key, name, ft_strlen(name)) == 0)
		{
			data = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (data);
}

int	ft_get_expanded_len(char *cmd, char *env_var)
{
	int		i;
	int		len;

	i = 0;
	while (cmd[i] != '$')
		i++;
	len = i;
	while (cmd[i] && cmd[i] != '\"' && cmd[i] != '\t')
		i++;
	while (cmd[i])
	{
		len++;
		i++;
	}
	return (len + ft_strlen(env_var) + 1);
}

char	*ft_replace_env_var(char *cmd, char *env_var)
{
	int		i;
	int		j;
	int		len;
	char	*new_cmd;

	i = 0;
	len = ft_get_expanded_len(cmd, env_var);
	new_cmd = (char *)malloc(len + ft_strlen(env_var) + 1);
	while (cmd[i] != '$')
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	j = i;
	while (cmd[j] && cmd[j] != '\"' && cmd[j] != '\t')
		j++;
	while (*env_var)
		new_cmd[i++] = *env_var++;
	while (cmd[i])
		new_cmd[i] = cmd[i];
	new_cmd[i] = '\0';
	printf("new_cmd: %s\n", cmd);
	return (new_cmd);
}

void	expand_env(t_token *token, t_env *env)
{
	int		i;
	char	*data;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == ENV && tmp->state != IN_SQUOTES)
		{
			tmp = tmp->next;
			data = ft_getenv(tmp->data, env);
			if (data)
			{
				data = ft_replace_env_var(tmp->data, data);
				free(tmp->data);
				tmp->data = data;
			}
		}
		tmp = tmp->next;
	}
}
