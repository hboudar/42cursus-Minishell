/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:33 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/18 08:34:44 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool	is_valid_name(const char *name)
{
	int	i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	ft_unsetenv(const char *name, t_env *env)
{
	int		underscor;
	int		mode;

	underscor = !ft_strncmp(name, "_", 2);
	while (env)
	{
		mode = (ft_strchr(env->key, '=') != NULL);
		if (!underscor && !ft_strncmp(env->key, name, ft_strlen(name))
			&& ft_strlen(env->key) - mode == ft_strlen(name))
		{
			env->print = NO_PRINT;
			break ;
		}
		else if (underscor && !ft_strncmp(env->key, "_=", 3))
		{
			free(env->value);
			env->value = NULL;
			env->value = ft_strdup("_");
			break ;
		}
		env = env->next;
	}
	return (0);
}

int	ft_unset(t_prompt *prompt, t_env **env)
{
	int	i;

	(1) && (i = 1, prompt->exit_state = 0);
	while (prompt->cmd->args[i])
	{
		if (is_valid_name(prompt->cmd->args[i]))
			ft_unsetenv(prompt->cmd->args[i], *env);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(prompt->cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			prompt->exit_state = 1;
		}
		i++;
	}
	return (prompt->exit_state);
}
