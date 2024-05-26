/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:55:40 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/26 12:13:45 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void sig_handler_child(int sig)
{
    printf("signal %d\n", sig);
    if (sig == SIGINT) {
        rl_clear_history();
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        write(1, "  \n", 3);
        exit(1);
    }
    else if (sig == SIGQUIT)
    {
        rl_clear_history();
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        printf("wash katprinti? \n");
        exit(131);
    }
}

void sigint_handler_heredoc(int sig)
{
    if (sig == SIGINT) {
        rl_clear_history();
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
        write(1, "  \n", 3);
        exit(1);
    }
}

void setup_signal_handlers(void (*int_handler)(int), void (*quit_handler)(int))
{
    rl_catch_signals = 1;
    signal(SIGINT, int_handler);
    signal(SIGQUIT, quit_handler);
}
