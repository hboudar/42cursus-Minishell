/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:25:47 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/01 17:59:37 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE_TKN)
			return (1);
		token = token->next;
	}
	return (0);
}

void	get_token_type(t_token *token)
{
	if (ft_strncmp(token->data, "|", 2) == 0)
		token->type = PIPE_TKN;
	else if (ft_strncmp(token->data, ">", 2) == 0)
		token->type = REDIR_OUT;
	else if (ft_strncmp(token->data, ">>", 3) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->data, "<", 4) == 0)
		token->type = REDIR_IN;
	else if (ft_strncmp(token->data, "$", 1) == 0)
		token->type = ENV;
	else if (ft_strncmp(token->data, "<<", 3) == 0)
		token->type = REDIR_HERE_DOC;
	else if (ft_iswhitespace(token->data))
		token->type = WHITE_SPACE;
	else
		token->type = WORD;
}

char	*ft_remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	get_token_state(t_token *token)
{
	if (ft_strncmp(token->data, "'", 1) == 0)
	{
		token->state = IN_SQUOTES;
		token->data = ft_remove_quotes(token->data);
	}
	else if (ft_strncmp(token->data, "\"", 1) == 0)
	{
		token->state = IN_DQUOTES;
		token->data = ft_remove_quotes(token->data);
	}
	else
		token->state = GENERAL;
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->next;
		free(tmp->data);
		free_tab(&tmp->expand);
		free(tmp);
	}
	*token = NULL;
}
