/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:31 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/19 14:53:32 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_prompt *prompt, t_env *env)
{
	char	*path;

	prompt->exit_state = 0;
	if (prompt->cmd->args[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	path = find_path(prompt->cmd->args, env);
	if (!path || !ft_strncmp(path, "env", 4))
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	free (path);
	while (env)
	{
		if (env->value && (env->print == ENV_PRINT || env->print == PRINT))
			printf("%s%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
