/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:01:29 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/06 15:51:19 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_pwd(t_prompt *prompt)
{
    char *pwd;
    
    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
    {
        perror("getcwd");
        return (prompt->exit_state);
    }
    printf("%s\n", pwd);
    free(pwd);
    prompt->exit_state = 0;
    return (prompt->exit_state);
}
