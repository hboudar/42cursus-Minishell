/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:16:38 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/29 20:17:24 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution.h"

int ft_and(t_prompt *prompt, t_env **env)
{
    if (!execution(prompt->left, env))
        return (execution(prompt->right, env));
    return (prompt->exit_state);
}