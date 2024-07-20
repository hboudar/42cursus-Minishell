/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:15:27 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 09:15:28 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_args(t_cmd *cmd, t_expand *expand, char **tmp, int i)
{
	int			j;
	int			len;
	char		**new_data;

	len = ft_tablen(cmd->args);
	new_data = malloc(sizeof(char *) * (len + ft_tablen(tmp)));
	j = -1;
	while (++j < i)
		new_data[j] = ft_strdup(cmd->args[j]);
	j = -1;
	while (tmp[++j])
		new_data[i + j] = ft_strdup(tmp[j]);
	while (cmd->args[i + 1])
	{
		new_data[i + j] = ft_strdup(cmd->args[i + 1]);
		i++;
	}
	new_data[i + j] = NULL;
	free_tab(&cmd->args);
	cmd->args = new_data;
	while (expand->next)
	{
		expand->index += len;
		expand = expand->next;
	}
}

char	*get_expanded_value(char **data, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, *data, ft_strlen(*data))
			&& ft_strlen(*data) == ft_strlen(tmp->key) - 1
			&& tmp->print != NO_PRINT)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_and_split(t_cmd *cmd, t_expand *expand, t_env *env)
{
	int		i;
	int		len;
	char	**tmp;
	char	*value;

	i = expand->index;
	value = get_expanded_value(&expand->data, env);
	tmp = ft_split_expand(value);
	len = ft_tablen(tmp);
	if (!value || len == 1)
	{
		remove_arg(cmd, expand->index, value);
		while (expand->next)
		{
			expand->index -= (len == 0);
			expand = expand->next;
		}
		return ;
	}
	if (len > 1)
		replace_args(cmd, expand, tmp, i);
	free_tab(&tmp);
}

void	get_expand(char **line, t_token *token)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_isword((*line)[i]) && (*line)[i] != '+' && (*line)[i] != '=')
		i++;
	tmp = ft_substr(*line, 0, i);
	*line = *line + i;
	add_last(&token->expand, tmp);
	free(tmp);
}

void	split_expand(t_token *token)
{
	char	*tmp;

	while (token)
	{
		if (token->state == IN_DQUOTES)
		{
			tmp = token->data;
			while (*tmp)
			{
				if (*tmp == '$')
				{
					tmp++;
					get_expand(&tmp, token);
				}
				else
					tmp++;
			}
		}
		token = token->next;
	}
}
