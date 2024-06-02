/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:16:38 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/02 13:19:50 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int ft_and(t_prompt *prompt, t_env **env, int *fd_out, int *fd_in)
{
    if (!execution(prompt->left, env, fd_out, fd_in))
        return (execution(prompt->right, env, fd_out, fd_in));
    return (prompt->exit_state);
}
