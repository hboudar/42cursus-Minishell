/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/02 14:52:26 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_new_data(char *args, t_expand *expand, int index, t_env *env, int len)
{
	int		i;
	int		j;
	char	*value;
	char	*new_data;

	value = get_expanded_value(&expand->data, env);
	len = ft_strlen(args) - ft_strlen(expand->data) + ft_strlen(value);
	new_data = malloc(len);
	ft_bzero(new_data, len);
	(1) && (i = -1, j = 0);
	while (args[++i] != '$')
		new_data[i] = args[i];
	index = i + ft_strlen(expand->data) + 1;
	while (value && value[j])
		new_data[i++] = value[j++];
	j = index;
	while (args[j])
		new_data[i++] = args[j++];
	new_data[i] = '\0';
	return (new_data);
}

void	expand_cmd(t_cmd *cmd, t_env *env)
{
	int			i;
	char		*tmp;
	t_expand	*expand;

	if (!cmd->expand)
		return ;
	expand = cmd->expand;
	while (expand)
	{
		i = cmd->expand->index;
		if (expand->quotes)
		{
			tmp = get_new_data(cmd->args[i], expand, i, env, 0);
			free(cmd->args[i]);
			cmd->args[i] = tmp;
		}
		else
			add_and_split(cmd, expand, env);
		expand = expand->next;
	}
}

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
}

t_cmd	*parse_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	fill_redirections(cmd, token);
	remove_redirections(&token);
	get_cmd(&cmd, token);
	free_token(&token);
	return (cmd);
}
