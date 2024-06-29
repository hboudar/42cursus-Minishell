/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:10:07 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/14 12:09:39 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
