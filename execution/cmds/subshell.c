/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:35:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/07 00:43:20 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int		subshell(t_prompt *prompt, t_env **env)
{
    int fd[2];
    pid_t pid;
    int i;

    printf("subshell\n");
    (1) && (i = -1, fd[0] = 0, fd[1] = 1);
    ignore_signals();
    pid = fork();
    if (pid == -1)
        error("fork");
    if (pid == 0)
    {
	    setup_signal_handlers(sig_handler_child, sig_handler_child);
        if (prompt->type == P_PIPE)
            prompt->exit_state = ft_pipe(prompt, env, fd[0]);
        else if (prompt->type == P_OR)
            prompt->exit_state = ft_or(prompt, env, fd[0]);
        else if (prompt->type == P_AND)
            prompt->exit_state = ft_and(prompt, env, fd[0]);
        exit(prompt->exit_state);
    }
    else
    {
        while (wait(&prompt->exit_state) != pid)
            continue ;
    }
    return (prompt->exit_state);
}

//expand_cmd

/*A subshell created by (…) has the same file descriptors as its creator.
Some other means of creating subshells modify some file descriptors before executing user code; for example,
the left-hand side of a pipe runs in a subshell3 with standard output connected to the pipe.
The subshell also starts out with the same current directory,
the same signal mask, etc.
One of the few exceptions is that subshells do not inherit custom traps: ignored signals (trap '' SIGNAL) remain ignored in the subshell,
but other traps (trap CODE SIGNAL) are reset to the default action4.*/
