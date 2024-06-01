/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/01 16:03:01 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_expand(t_expand **expand, char *data, int index, enum e_state state)
{
	t_expand	*new;
	t_expand	*tmp;

	new = (t_expand *)malloc(sizeof(t_expand));
	new->data = ft_strdup(data);
	new->index = index;
	new->quotes = (state == IN_DQUOTES);
	new->next = NULL;
	if (!*expand)
	{
		*expand = new;
		return ;
	}
	tmp = *expand;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	get_cmd(t_cmd **cmd, t_token *token)
{
	int		i;
	int		j;
	int		k;
	char	**args;

	(1) && (i = 0, j = 0);
	if (token)
		args = (char **)malloc(sizeof(char *) * (token->size + 1));
	else
		args = NULL;
	while (token)
	{
		k = 0;
		args[j] = ft_strdup(token->data);
		while (token->expand && token->expand[k])
			add_expand(&(*cmd)->expand, token->expand[k++], j, token->state);
		j++;
		token = token->next;
	}
	if (args)
		args[j] = NULL;
	(*cmd)->type = HERE_DOC * ((*cmd)->limiter != NULL);
	(*cmd)->args = args;
	(*cmd)->size = j;
}

t_cmd	*parse_cmd(t_token *token, t_env *env)
{
	t_cmd	*cmd;

	(void)env;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	fill_redirections(cmd, token);
	remove_redirections(&token);
	get_cmd(&cmd, token);
	free_token(token);
	return (cmd);
}
