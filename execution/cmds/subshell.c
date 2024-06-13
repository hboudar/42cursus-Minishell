/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:35:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/13 18:16:29 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int		subshell(t_prompt *prompt, t_env **env)
{
    pid_t pid;

    printf("subshell\n");
    prompt->subshell = 0;
    ignore_signals();
    pid = fork();
    if (pid == -1)
        error("fork");
    if (pid == 0)
    {
        setup_signal_handlers(sig_handler_child, sig_handler_child);
        non_redirection(prompt, *env, prompt->file);
        exit (execution(prompt, env));
    }
    else
    {
        while (wait(&prompt->exit_state) != pid)
            continue ;
        prompt->exit_state = WEXITSTATUS(prompt->exit_state);
    }
    return (prompt->exit_state);
}
