/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:25:47 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/22 18:27:22 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE)
			return (1);
		token = token->next;
	}
	return (0);
}

void	get_token_type(t_token *token)
{
	if (ft_strncmp(token->data, ">", 1) == 0)
		token->type = REDIR_OUT;
	else if (ft_strncmp(token->data, ">>", 2) == 0)
		token->type = REDIR_APPEND;
	else if (ft_strncmp(token->data, "<", 1) == 0)
		token->type = REDIR_IN;
	else if (ft_strncmp(token->data, "<<", 2) == 0)
		token->type = REDIR_HERE_DOC;
	else if (ft_strncmp(token->data, "|", 1) == 0)
		token->type = PIPE;
	else
		token->type = WORD;
}

void	get_token_state(t_token *token)
{
    if (ft_strncmp(token->data, "'", 1) == 0)
        token->state = IN_SQUOTES;
    else if (ft_strncmp(token->data, "\"", 1) == 0)
        token->state = IN_DQUOTES;
    else
        token->state = GENERAL;
}

void	set_size(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	token->size = i + 1;
	if (token->next)
		set_size(token->next);
}

t_token	*parse_token(char *line)
{
	t_token	*token;
	t_token	*tmp;
	size_t	i;

	i = 0;
	token = (t_token *)malloc(sizeof(t_token));
	tmp = token;
	while (i <= ft_strlen(line))
	{
		if (line[i] == ' ' || line[i] == '\0')
		{
			tmp->data = ft_substr(line, 0, i);
			get_token_type(tmp);
			get_token_state(tmp);
			line = line + i + 1;
			i = 0;
			tmp->next = (t_token *)malloc(sizeof(t_token));
			tmp = tmp->next;
		}
		i++;
	}
	tmp->next = NULL;
	set_size(token);
	return (token);
}
