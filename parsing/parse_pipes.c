/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:54:04 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/26 19:17:45 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_pipe(t_token *token)
{
    t_token	*tmp;

    tmp = token;
    while (tmp)
    {
        if (tmp->type == PIPE_TKN)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}

t_token	*get_pipe(t_token *token)
{
    t_token	*tmp;

    tmp = token;
    while (tmp)
    {
        if (tmp->type == PIPE_TKN)
            return (tmp->next);
        tmp = tmp->next;
    }
    return (NULL);
}

void	handle_pipe(t_prompt **prmpt, t_token **token, t_env *env)
{
	t_token	*tmp;
	t_token	*pipeless;

	if (!check_pipe(*token))
	{
		(*prmpt)->left = NULL;
		(*prmpt)->right = NULL;
		(*prmpt)->type = P_CMD;
		parse_cmd(*token, env);
		return ;
	}
	tmp = get_pipe(*token);
	pipeless = remove_pipe(*token);
	(*prmpt)->left = malloc(sizeof(t_prompt));
	(*prmpt)->right = malloc(sizeof(t_prompt));
    handle_pipe(&(*prmpt)->left, &pipeless, env);
    handle_pipe(&(*prmpt)->right, &tmp, env);
	(*prmpt)->type = P_PIPE;
}
