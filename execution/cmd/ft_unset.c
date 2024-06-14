/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:33 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 02:25:20 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

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

static void	ft_unsetenv(const char *name, t_env **env)
{
	t_env	*prev;
	t_env	*tmp;
	int		mode;

	if (ft_strncmp(name, "_", 2) == 0)
		return ;
	(1) && (tmp = *env, prev = NULL);
	while (tmp)
	{
		mode = (ft_strchr(tmp->key, '=') != NULL);
		if (!ft_strncmp(tmp->key, name, ft_strlen(name))
			&& ft_strlen(tmp->key) - mode == ft_strlen(name))
		{
			(tmp->key) && (free(tmp->key), tmp->key = NULL);
			(tmp->value) && (free(tmp->value), tmp->value = NULL);
			if (prev != NULL)
				prev->next = tmp->next;
			else
				*env = (*env)->next;
			free(tmp);
			tmp = NULL;
			break ;
		}
		(1) && (prev = tmp, tmp = tmp->next);
	}
}

int	ft_unset(t_prompt *prompt, t_env **env)
{
	int	exit_state;
	int	i;

	(1) && (i = 1, exit_state = 0);
	while (prompt->cmd->args[i])
	{
		if (is_valid_name(prompt->cmd->args[i]))
			ft_unsetenv(prompt->cmd->args[i], env);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(prompt->cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_state = 1;
		}
		i++;
	}
	return (exit_state);
}
