/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:17:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/07 00:43:51 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../execution.h"

int	ft_or(t_prompt *prompt, t_env **env, int fd_in)
{
	printf("ft_or\n");
	prompt->exit_state = execution(prompt->left, env, fd_in);
	if (prompt->exit_state)
		prompt->exit_state = execution(prompt->right, env, fd_in);
	return (prompt->exit_state);
}


/*
		if (prompt->left->type == P_CMD)
			prompt->exit_state = ft_cmd(prompt->left, env);
		else if (prompt->left->type == P_PIPE)
			prompt->exit_state = ft_pipe(prompt->left, env, fd_in);
		else if (prompt->left->type == P_OR)
			prompt->exit_state = ft_or(prompt->left, env, fd_in);
		else if (prompt->left->type == P_AND)
			prompt->exit_state = ft_and(prompt->left, env, fd_in);
		if (prompt->exit_state)
		{
			if (prompt->right->type == P_CMD)
				prompt->exit_state = ft_cmd(prompt->right, env);
			else if (prompt->right->type == P_PIPE)
				prompt->exit_state = ft_pipe(prompt->right, env, fd_in);
			else if (prompt->right->type == P_OR)
				prompt->exit_state = ft_or(prompt->right, env, fd_in);
			else if (prompt->right->type == P_AND)
				prompt->exit_state = ft_and(prompt->right, env, fd_in);
		}
	
*/