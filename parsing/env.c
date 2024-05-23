/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:10:07 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/22 23:35:40 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_getenv(char *name, t_env *env)
{
	char	*data;

	data = NULL;
	while (env)
	{
		printf("env->key: %s\n", env->key);
		printf("name: %s\n", name);
		if (!ft_strncmp(env->key, name, ft_strlen(name)))
		{
			data = ft_strdup(env->value);
			break ;
		}
		env = env->next;
	}
	if (!data)
		data = ft_strdup("");
	return (data);
}

void	expand_env(t_token **token, t_env *env)
{
	int		i;
	char	*data;
	t_token	*tmp;
	t_token	*tmp2;

	i = 0;
	tmp = *token;
	if (!tmp->data)
		return ;
	while (tmp->next && tmp->next->type == WHITE_SPACE)
		tmp2 = tmp->next;
	remove_token(token, tmp);
	tmp = tmp2;
	data = ft_getenv(tmp->data, env);
	free(tmp->data);
	tmp->data = data;
}

void	expand_tokens(t_token **token, t_env *env)
{
    t_token	*tmp;

    tmp = *token;
    while (tmp)
    {
        if (tmp->type == ENV)
		{
			if (tmp == (*token))
				expand_env(token, env);
			else
            	expand_env(&tmp, env);
		}
        tmp = tmp->next;
    }
}
