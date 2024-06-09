/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:35:11 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/09 16:30:29 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

static int  ft_outredirect(t_prompt *prompt, int *out, int *fd)
{
    (*out != 1) && (close(*out));
    if (prompt->file->type == 1)
        *out = open(prompt->file->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (prompt->file->type == 2)
        *out = open(prompt->file->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (*out == -1)
    {
        close(fd[0]);
        perror(prompt->file->data);
        return (0);
    }
    if (dup2(*out, 1) == -1)
    {
        close(fd[0]);
        close(*out);
        perror("dup2 in out");
        return (0);
    }
    return (1);
}

static int	ft_inredirect(t_prompt *prompt, int *in, int *fd)
{
    (*in != 0) && (close(*in));
    *in = open(prompt->file->data, O_RDONLY);
    if (*in == -1)
    {
        close(fd[0]);
        perror(prompt->file->data);
        return (0);
    }
    if (dup2(*in, 0) == -1)
    {
        close(fd[0]);
        close(*in);
        perror("dup2 in in");
        return (0);
    }
    return (1);
}

int    ft_redirection(t_prompt *prompt, int *fd)
{
    int in;
    int out;
    int err;

    (void)fd;
    (1) && (in = 0, out = 1, err = 1);
    while (prompt->file)
    {
        if (prompt->file->type == 0 || prompt->file->type == 3)
            err = ft_inredirect(prompt, &in, fd);
        else if (prompt->file->type)
            err = ft_outredirect(prompt, &out, fd);
        if (!err)
        {
            printf("err\n");
            exit(1);
        }
        prompt->file = prompt->file->next;
    }
    return (1);
}

int sub_fork(t_prompt *prompt, t_env **env, int *fd)
{
    pid_t pid;

    ignore_signals();
    pid = fork();
    if (pid == -1)
        error("fork");
    if (pid == 0)
    {
        setup_signal_handlers(sig_handler_child, sig_handler_child);
        ft_redirection(prompt, fd);
        exit (execution(prompt, env, fd[0]));
    }
    else
    {
        while (wait(&prompt->exit_state) != pid)
            continue ;
    }
    return (prompt->exit_state);
}

int		subshell(t_prompt *prompt, t_env **env)
{
    extern int  g_caught;
    int fd[2];
    int i;

    (1) && (i = -1, fd[0] = 0, fd[1] = 1, prompt->subshell = 0, g_caught = 0);
    while (prompt->limiter && !g_caught && prompt->limiter[++i])
        here_doc(prompt, i, fd);
    if (g_caught)
    {
        g_caught = 0;
        close(fd[0]);
        return (1);
    }
    return (sub_fork(prompt, env, fd));
}

//expand_cmd

/*A subshell created by (…) has the same file descriptors as its creator.
Some other means of creating subshells modify some file descriptors before executing user code; for example,
the left-hand side of a pipe runs in a subshell3 with standard output connected to the pipe.
The subshell also starts out with the same current directory,
the same signal mask, etc.
One of the few exceptions is that subshells do not inherit custom traps: ignored signals (trap '' SIGNAL) remain ignored in the subshell,
but other traps (trap CODE SIGNAL) are reset to the default action4.*/
