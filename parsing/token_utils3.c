/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:24:04 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/15 17:00:30 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*get_limit(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE_TKN || tmp->type == AND_TOKEN
			|| tmp->type == OR_TOKEN)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_token(t_token *new_token)
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

void	tokenize_semicolon(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup(";");
	(*token)->size = 1;
	(*token)->type = SEMI_COLON;
	(*token)->state = GENERAL;
	*line = *line + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}

void	tokenize_error(char **line, int *i, t_token **token)
{
	(*token)->data = ft_strdup("&");
	(*token)->size = 1;
	(*token)->type = ERROR;
	(*token)->state = GENERAL;
	*line = *line + 1;
	*i = 0;
	(*token)->next = (t_token *)malloc(sizeof(t_token));
	(*token) = (*token)->next;
	ft_bzero(*token, sizeof(t_token));
}
