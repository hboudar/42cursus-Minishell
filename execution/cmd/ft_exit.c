/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:53:52 by hboudar           #+#    #+#             */
/*   Updated: 2024/07/19 14:53:53 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_exit_error(t_prompt *prompt)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(prompt->cmd->args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	prompt->exit_state = 255;
	exit(255);
}

static unsigned char	costum_atoi(const char *s, t_prompt *prompt)
{
	unsigned long	n_ll;
	unsigned long	n;
	int				sign;
	int				i;

	(1) && (i = 0, n_ll = 0, n = 0);
	while ((s[i] == 32 || (s[i] >= 9 && s[i] <= 13)) && s[i])
		i++;
	sign = (s[i] == '-') * -1 + (s[i] == '+' || s[i] != '-');
	i += (s[i] == '-' || s[i] == '+');
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			n = n * 10 + s[i] - 48;
			if (n / 10 != n_ll)
				ft_exit_error(prompt);
			n_ll = n;
		}
		else
			ft_exit_error(prompt);
		i++;
	}
	return ((unsigned char)(n * sign));
}

static int	ft_exit_2(t_prompt *prompt)
{
	extern int	g_caught;

	printf("exit\n");
	if (!prompt)
		exit(g_caught);
	exit (prompt->exit_state);
}

int	ft_exit(t_prompt *prompt)
{
	int	i;

	if (prompt && prompt->cmd && prompt->cmd->args[1] != NULL)
	{
		i = 0;
		while (ft_isdigit(prompt->cmd->args[1][i]))
			i++;
		if (prompt->cmd->args[1][i] != '\0')
			ft_exit_error(prompt);
		else
		{
			prompt->exit_state = (int)costum_atoi(prompt->cmd->args[1], prompt);
			if (prompt->cmd->args[2] != NULL)
				return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
			else
			{
				printf("exit\n");
				exit(prompt->exit_state);
			}
		}
	}
	return (ft_exit_2(prompt));
}
