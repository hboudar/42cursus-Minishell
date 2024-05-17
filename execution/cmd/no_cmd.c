/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:13:54 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/17 15:54:38 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

// if (!prompt->cmd->file)
//     {
//         printf("no prompt but reach here\n");
//         return (0);
//     }
//     while (prompt->cmd->file)
//     {
//         if (prompt->cmd->file->type == INFILE)
//             ft_infile(prompt);
//         else if (prompt->cmd->file->type == OUTFILE)
//             ft_outfile(prompt);
//         prompt->cmd->file = prompt->cmd->file->next;
//     }

// static void    ft_infile(t_prompt *prompt)
// {
//     int fd;

//     fd = open(prompt->cmd->infile->data, O_RDONLY);
//     if (fd == -1)
//     {
//         printf ("%s: %s: No such file or directory\n", prompt->cmd->infile->data, strerror(errno));
//         prompt->exit_state = 1;
//         return ;
//     }
//     prompt->exit_state = 0;
// }

// static void   ft_outfile(t_prompt *prompt)
// {
//     int fd;

//     while (prompt->cmd->outfile)
//     {
//         if (prompt->cmd->outfile->appendable)
//         {
//             fd = open(prompt->cmd->outfile->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
//             if (fd == -1)
//             {
//                 printf ("%s: %s: No such file or directory\n", prompt->cmd->outfile->data, strerror(errno));
//                 prompt->exit_state = 1;
//                 return ;
//             }
//         }
//         else
//             fd = open(prompt->cmd->outfile->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         prompt->cmd->outfile = prompt->cmd->outfile->next;
//     }
// }

static void    ft_redirect(t_prompt *prompt)
{
    if (!prompt->cmd->file)
        return ;
    while (prompt->cmd->file)
    {
        ;
    }
}

static void	here_doc(t_prompt *prompt)
{
	char	*str;
    char    *limiter;

    limiter = prompt->cmd->limiter[0];
	while (1)
	{
		str = readline("> ");
		if (ft_strlen(str) - 1 == ft_strlen(limiter)
			&& !ft_strncmp(str, limiter, ft_strlen(limiter)))
		{
			free(str);
			str = NULL;
			exit(0);
		}
		free(str);
		str = NULL;
	}
}

int    no_cmd(t_prompt *prompt)
{
    if (prompt->cmd->type == HERE_DOC)
        here_doc(prompt);
    ft_redirect(prompt);
    return (prompt->exit_state);
}
