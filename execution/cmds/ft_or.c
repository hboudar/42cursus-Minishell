/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:17:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/02 14:49:51 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int	ft_or(t_prompt *prompt, t_env **env, int *fd_out, int *fd_in)
{
	if (execution(prompt->left, env, *fd_out, *fd_in))
		return (execution(prompt->right, env, *fd_out, *fd_in));
	return (prompt->exit_state);
}
