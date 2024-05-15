/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/15 19:53:31 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fix_quotes(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp)
	{
		 
	}
}

void	get_cmd(t_cmd **cmd, t_token *token)
{
	int		i;
	int		j;
	char	**args;

	i = 0;
	j = 0;
	if (token)
		args = (char **)malloc(sizeof(char *) * (token->size + 1));
	else
		args = NULL;
	while (token)
	{
		args[j] = ft_strdup(token->data);
		j++;
		token = token->next;
	}
	if (token)
		args[j] = NULL;
	(*cmd)->type = CMD * ((*cmd)->limiter == NULL);
	(*cmd)->args = args;
	(*cmd)->size = j;
}

t_cmd	*parse_cmd(t_token *token, t_env *env)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	// fix_quotes(token);
	expand_env(token, env);
	fill_redirections(cmd, token);
	remove_redirections(&token);
	get_cmd(&cmd, token);
	return (cmd);
}
