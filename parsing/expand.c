/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:20:59 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/30 20:36:57 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_expanded_len(t_token *to_expand, int size)
{
	int		len;
	char	*tmp;
	char	**tmp_expand;

	tmp_expand = to_expand->expand;
	(1) && (tmp = to_expand->data, len = ft_strlen(tmp));
	while (*tmp)
	{
		if (*tmp == '$')
		{
			tmp++;
			while (ft_isword(*tmp))
			{
				tmp++;
				len--;
			}
			len += ft_strlen(tmp_expand[size--]);
		}
		tmp++;
	}
	return (len);
}

int	is_empty(char **expand, int size)
{
	int	i;
	int	empty;

	i = 0;
	empty = 0;
	while (i < size)
	{
		if (!expand[i])
			empty++;
		i++;
	}
	return (empty);
}

void	get_expand(char **line, t_token *token)
{
	int		i;
	char	*tmp;

	i = 0;
	while (ft_isword((*line)[i]))
		i++;
	tmp = ft_substr(*line, 0, i);
	*line = *line + i;
	add_last(&token->expand, tmp);
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
				tmp++;
			}
		}
		token = token->next;
	}
}

void	expand_data(t_token *to_expand, int size, int j, int k)
{
	int		i;
	int		len;
	char	*tmp;
	char	*new_data;

	i = 0;
	len = get_expanded_len(to_expand, size);
	new_data = (char *)malloc(sizeof(char) * (len + 1));
	ft_bzero(new_data, len);
	tmp = to_expand->data;
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			i++;
			while (ft_isword(tmp[i]))
				i++;
			new_data = ft_strjoin(new_data, to_expand->expand[j]);
			k += ft_strlen(to_expand->expand[j++]);
		}
		else
			new_data[k++] = tmp[i++];
	}
	free(to_expand->data);
	to_expand->data = new_data;
}
