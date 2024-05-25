/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:55:40 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/25 13:05:44 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void sigint_handler_heredoc(int sig)
{
    extern int g_caught;
    if (sig == SIGINT) {
        restore_default_signal_handlers();
        rl_clear_history();
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        g_caught = 1;
        write(1, "\n", 1);
        exit(1);
    }
}

void setup_signal_handlers(void (*int_handler)(int), void (*quit_handler)(int))
{
    rl_catch_signals = 1;
    signal(SIGINT, int_handler);
    signal(SIGQUIT, quit_handler);
}

void restore_default_signal_handlers()
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
