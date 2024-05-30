/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:00:37 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/30 20:34:18 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_token(t_token **token, t_token *new_token)
{
	int		i;
	char	**tmp;
	t_token	*tmp_token1;

	i = 0;
	tmp = ft_split(new_token->data, ' ');
	while (tmp[i])
	{
		if (i == 0)
		{
			free(new_token->data);
			new_token->data = ft_strdup(tmp[i]);
		}
		else
		{
			tmp_token1 = (t_token *)malloc(sizeof(t_token));
			tmp_token1->data = ft_strdup(tmp[i]);
			tmp_token1->type = WORD;
			tmp_token1->state = new_token->state;
			tmp_token1->next = new_token->next;
			new_token->next = tmp_token1;
			new_token = new_token->next;
		}
		i++;
	}
}
