/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:04 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/25 17:08:58 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int ft_cd(t_prompt *prompt)
{
    char *oldpwd;
    char *pwd;
    int  i;

    oldpwd = getcwd(NULL, 0);
    if (chdir(prompt->cmd->args[1]) == -1)
    {
        free(oldpwd);
        return (i);
    }
    pwd = getcwd(NULL, 0);
    
    return (0);
}

/*
    int chdir(const char *path);
    
Common Errors:
        ENOENT: The specified path doesn't exist.
        EACCES: You lack the necessary permissions to access the target directory.
        ENOTDIR: A component of the path is not a directory (e.g., you tried to change to a file instead of a directory).
        ELOOP: There's an infinite loop of symbolic links encountered while resolving the path.
*/