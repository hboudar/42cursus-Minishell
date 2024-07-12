/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:21:11 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 09:21:12 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int signum)
{
	extern int	g_caught;

	if (signum == SIGINT)
	{
		g_caught = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(t_prompt *prompt, int mode)
{
	extern int	g_caught;

	if (g_caught == 0)
	{
		rl_catch_signals = 0;
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		if (prompt)
			prompt->exit_state = 1;
		if (!mode)
			g_caught = 0;
	}
}
