/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/09 01:28:00 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_data_type(t_data *data)
{
	char	*tmp;

	if (!data)
		return ;
	tmp = data->arg;
	while (tmp && *tmp)
	{
		if (*tmp == '$')
			break ;
		tmp++;
	}
	if (*tmp == '$')
		data->type = ENV;
	else
		data->type = WORD;
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

void	fill_expand(t_cmd *cmd, t_token *token)
{
	int		i;
	int		j;
	t_token	*tmp;

	tmp = token;
	i = 0;
	while (tmp)
	{
		if (tmp->expand)
		{
			j = 0;
			while (tmp->expand[j])
			{
				add_expand(&cmd->expand, tmp->expand[j], i, tmp->state);
				j++;
			}
		}
		tmp = tmp->next;
		i++;
	}
}

char	*get_new_data(char *args, t_expand *expand, int index, t_env *env)
{
	int		i;
	int		j;
	int		len;
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

void	expand_cmd(t_prompt *prmpt, t_env *env)
{
	char		*tmp;
	t_data		*data;
	t_expand	*expand;

	data = prmpt->cmd->data;
	expand = prmpt->cmd->expand;
	while (expand)
	{
		while (data)
		{
			while (data && data->type == ENV && ft_strncmp(data->arg, "$?", 3))
			{
				tmp = get_new_data(data->arg, expand, 0, env);
				split_expanded(prmpt, &data, tmp);
				set_data_type(data);
				expand = expand->next;
			}
			if (data && data->type == ENV && !ft_strncmp("$?", data->arg, 3))
				replace_exit_state(prmpt, data);
			(data) && (data = data->next);
		}
		(expand) && (expand = expand->next);
	}
	get_args(prmpt->cmd);
}
