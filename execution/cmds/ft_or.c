/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:17:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/04 21:44:08 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int	ft_or(t_prompt *prompt, t_env **env, int fd_in)
{
	printf("FT_OR\n");
	prompt->exit_state = execution(prompt->left, env, fd_in);
	if (prompt->exit_state)
		prompt->exit_state = execution(prompt->right, env, fd_in);
	return (prompt->exit_state);
}
