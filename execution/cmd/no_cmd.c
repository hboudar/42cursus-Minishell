/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/15 16:46:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int    no_cmd(t_prompt *prompt)
{
    int fd;

    if (prompt->cmd->infile)
    {
        fd = open(prompt->cmd->infile->data, O_RDONLY);
        if (fd == -1)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(prompt->cmd->infile->data, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            prompt->exit_state = 1;
        }
    }
    if (prompt->cmd->outfile)
    {
        while (prompt->cmd->outfile)
        {
            if (prompt->cmd->outfile->appendable)
                open(prompt->cmd->outfile->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                open(prompt->cmd->outfile->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            prompt->cmd->outfile = prompt->cmd->outfile->next;
        }
    }
    return (0);
}
