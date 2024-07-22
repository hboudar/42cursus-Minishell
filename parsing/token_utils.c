/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:23:32 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/22 09:44:16 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE_TKN)
			return (1);
		token = token->next;
	}
	return (0);
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->data);
		free_tab(&tmp->expand);
		free(tmp);
	}
	*token = NULL;
}
