/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:14:53 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/16 11:08:25 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	split_expanded(t_prompt *prmpt, t_data **data, char *expanded)
{
	char	**new_data;

	if ((*data)->state == GENERAL)
	{
		new_data = ft_split_expand(expanded);
		free((*data)->arg);
		(*data)->arg = ft_strdup("");
		add_data(&prmpt->cmd->data, data, new_data, (*data)->joinable);
		(*data)->joinable = 1;
		free_tab(&new_data);
		free(expanded);
	}
	else
	{
		free((*data)->arg);
		(*data)->arg = expanded;
	}
}

void	remove_arg(t_cmd *cmd, int i, char *to_add)
{
	int		j;
	int		len;
	char	**new_data;

	j = -1;
	len = (to_add != NULL);
	new_data = malloc(sizeof(char *) * (ft_tablen(cmd->args) + len));
	ft_bzero(new_data, sizeof(char *) * (ft_tablen(cmd->args) + len));
	while (++j < i)
		new_data[j] = ft_strdup(cmd->args[j]);
	if (len)
		new_data[j] = ft_strdup(to_add);
	j++;
	while (cmd->args[j])
	{
		new_data[j - (len == 0)] = ft_strdup(cmd->args[j]);
		j++;
	}
	new_data[j - (len == 0)] = NULL;
	free_tab(&cmd->args);
	cmd->args = new_data;
}

int	ft_count_expand(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			i++;
		else
		{
			count++;
			while (str[i] && !ft_is_whitespace(str[i]))
				i++;
		}
	}
	return (count);
}

char	**ft_split_expand(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**newtab;

	if (!str)
		return (NULL);
	newtab = malloc(sizeof(char *) * (ft_count_expand(str) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			i++;
		else
		{
			k = i;
			while (str[i] && !ft_is_whitespace(str[i]))
				i++;
			newtab[j] = ft_substr(str, k, i - k);
			j++;
		}
	}
	newtab[j] = NULL;
	return (newtab);
}

char	**ft_dupexpand(char **expand)
{
	int		i;
	char	**newtab;

	if (!expand)
		return (NULL);
	newtab = malloc(sizeof(char *) * (ft_tablen(expand) + 1));
	i = 0;
	while (expand[i])
	{
		newtab[i] = ft_strdup(expand[i]);
		i++;
	}
	newtab[i] = NULL;
	return (newtab);
}
