/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/06/09 20:01:15 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execution(t_prompt *prompt, t_env **env, int std_in)
{
	printf("execution\n");
	if (prompt->subshell)
		return (subshell(prompt, env));
	else if (prompt->type == P_CMD)
		prompt->exit_state = ft_cmd(prompt, env);
	else if (prompt->type == P_PIPE)
		prompt->exit_state = ft_pipe(prompt, env, std_in);
	else if (prompt->type == P_OR)
		prompt->exit_state = ft_or(prompt, env, std_in);
	else if (prompt->type == P_AND)
		prompt->exit_state = ft_and(prompt, env, std_in);
	return (prompt->exit_state);
}
