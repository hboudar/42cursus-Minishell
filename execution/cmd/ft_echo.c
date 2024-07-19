/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:03 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/19 16:37:01 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_options(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	else if (str[1] == '\0')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_print(t_prompt *prompt, int option)
{
	int	i;

	i = option;
	while (prompt->cmd->args[i])
	{
		ft_putstr_fd(prompt->cmd->args[i], 1);
		if (prompt->cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option - 1 == 0)
		ft_putstr_fd("\n", 1);
}

int	ft_echo(t_prompt *prompt)
{
	int	option;
	int	i;

	prompt->exit_state = 0;
	if (prompt->cmd->args[1])
	{
		(1) && (option = 1, i = 1);
		while (prompt->cmd->args[i] != NULL)
		{
			if (check_options(prompt->cmd->args[i]))
			{
				option++;
				i++;
			}
			else
				break ;
		}
		ft_print(prompt, option);
	}
	else
		ft_putstr_fd("\n", 1);
	return (0);
}
