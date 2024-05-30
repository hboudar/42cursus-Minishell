/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:36:55 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/29 19:55:21 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execution(t_prompt *prompt, t_env **env)
{
	if (prompt->type == P_CMD)
		return (ft_cmd(prompt, env));
	else if (prompt->type == P_PIPE)
		return (ft_pipe(prompt, env));
	else if (prompt->type == P_OR)
		return (ft_or(prompt, env));
	else if (prompt->type == P_AND)
		return (ft_and(prompt, env));
	return (0);
}
