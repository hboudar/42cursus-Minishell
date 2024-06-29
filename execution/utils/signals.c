/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:55:40 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/14 11:27:08 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error(char *msg)
{
	perror(msg);
	return (1);
}

void	sig_handler_child(int sig)
{
	extern int	g_caught;

	printf("signal %d\n", sig);
	if (sig == SIGINT)
	{
		g_caught = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		exit(1);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_caught = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		exit(131);
	}
}

void	sigint_handler_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \n", 3);
		exit(1);
	}
}

void	setup_signal_handlers(void (*int_)(int), void (*quit_)(int))
{
	rl_catch_signals = 1;
	signal(SIGINT, int_);
	signal(SIGQUIT, quit_);
}
