/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:20:59 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/30 15:12:35 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    get_expand(char **line, t_token *token)
{
	int		i;
    char    *tmp;

	i = 0;
	while ((*line)[i] && (*line)[i] != ' ' && (*line)[i] != '|'
			&& (*line)[i] != '<' && (*line)[i] != '>'
			&& (*line)[i] != '&' && (*line)[i] != '\''
			&& (*line)[i] != '\"' && (*line)[i] != '('
			&& (*line)[i] != ')')
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
