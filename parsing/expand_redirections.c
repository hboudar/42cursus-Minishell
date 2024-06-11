/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:19:36 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/11 04:06:28 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	expand_redirections(t_token **token, t_env *env)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == APPEND)
		{
			if (tmp->next->state == IN_DQUOTES || tmp->next->state == GENERAL)
				expand_here_doc(&tmp->next->data, env, 0);
			tmp = tmp->next;
			if (ft_strncmp(tmp->data, "", 1) == 0 && tmp->state == GENERAL)
			{
				printf("minishell: ambiguous redirect\n");
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
