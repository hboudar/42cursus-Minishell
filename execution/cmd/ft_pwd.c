/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:29 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/18 12:18:29 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_getcwd(t_env *env)
{
	char	*path;

	(1) && (path = NULL, path = getcwd(NULL, 0));
	while (!path && env)
	{
		if (!ft_strncmp(env->key, "PWD=", 5))
			break ;
		env = env->next;
	}
	if (!path)
		return (ft_strdup(env->value));
	return (path);
}

int	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = ft_getcwd(env);
	if (!pwd)
	{
		perror("pwd failed");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
