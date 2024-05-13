/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:10:07 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/13 13:23:22 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_getenv(char *name, t_env *env)
{
	char	*data;

	data = NULL;
	while (env)
	{
		if (!ft_strncmp(env->key, name, ft_strlen(name)))
		{
			data = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	return (data);
}

void	expand_env(t_token *token, t_env *env)
{
	int		i;
	char	*data;
	t_token	*tmp;
	t_token	*tmp2;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == ENV && tmp->next && tmp->next->state == ENVIROMENT)
		{
			tmp2 = tmp->next;
			remove_token(&token, tmp);
			tmp = tmp2;
			data = ft_getenv(tmp->data, env);
			// free(tmp->data);
			if (data)
				tmp->data = data;
			else
				remove_token(&token, tmp);
		}
		tmp = tmp->next;
	}
}
