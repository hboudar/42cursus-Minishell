/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/07 22:40:26 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_cmd(t_cmd **cmd, t_token *token)
{
	int		i;
	int		j;
	char	**args;
	t_token	*tmp;

	i = 0;
	j = 0;
	args = (char **)malloc(sizeof(char *) * (token->size + 1));
	tmp = token;
	while (tmp)
	{
		args[j] = ft_strdup(tmp->data);
		j++;
		tmp = tmp->next;
	}
	args[j] = NULL;
	(*cmd)->type = CMD;
	(*cmd)->args = args;
	(*cmd)->size = j;
}

t_cmd	*parse_cmd(t_token	*token, t_env *env)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	expand_env(token, env);
	get_cmd(&cmd, token);
	return (cmd);
}
