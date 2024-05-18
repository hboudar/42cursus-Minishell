/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:55:40 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/18 21:50:32 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

//for signals only

void    signal_handler(int sig)
{
    extern int g_caught;

    if (sig == SIGINT && g_caught == 2)
    {
        write(1, "\n", 1);
        exit(1);
    }
}
