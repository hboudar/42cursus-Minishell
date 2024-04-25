/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:25:47 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/24 18:28:06 by aoulahra         ###   ########.fr       */
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

int	ft_iswhitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
			return (1);
		i++;
	}
	return (0);
}

void	get_token_type(t_token *token)
{
	if (ft_strncmp(token->data, "|", 2) == 0)
		token->type = PIPE;
	else if (ft_strncmp(token->data, ">", 2) == 0)
		token->type = REDIR_OUT;
	else if (ft_strncmp(token->data, ">>", 3) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->data, "<", 4) == 0)
		token->type = REDIR_IN;
	else if (ft_strncmp(token->data, "\"", 2) == 0)
		token->type = DQUOTE;
	else if (ft_strncmp(token->data, "'", 2) == 0)
		token->type = SQUOTE;
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
	int	i;
	int	j;
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

void print_tokens(t_token *token)
{
	t_token *tmp;
	int i;
	int space_left;

	tmp = token;
	printf("-------------------------------------------------------------------------------\n");
	printf("|    Value           |    Lenght        |    State         |    Type          |\n");
	printf("-------------------------------------------------------------------------------\n");
	while (tmp->data)
	{
		i = 0;
		space_left = 14 - ft_strlen(tmp->data);
		printf("|    '%s'", tmp->data);
		while (i < space_left)
		{
			printf(" ");
			i++;
		}
		i = 0;
		space_left = 14 - ft_strlen(ft_itoa(tmp->size));
		printf("|    %d", tmp->size);
		while (i < space_left)
		{
			printf(" ");
			i++;
		}
		i = 0;
		switch (tmp->state)
		{
		case 0:
			printf("|    IN_SQUOTE");
			break;
		case 1:
			printf("|    IN_DQUOTE");
			break;
		case 2:
			printf("|    GENERAL");
			break;
		}
		switch (tmp->state)
		{
		case 0:
			space_left = 14 - ft_strlen("GENERAL");
			break;
		case 1:
			space_left = 14 - ft_strlen("IN_QUOTE");
			break;
		case 2:
			space_left = 14 - ft_strlen("IN_DQUOTE");
			break;
		}
		while (i < space_left)
		{
			printf(" ");
			i++;
		}
		i = 0;
		char *new_type;
		if (tmp->type == SQUOTE)
			new_type = "QUOTE";
		else if (tmp->type == DQUOTE)
			new_type = "DOUBLE_QUOTE";
		else if (tmp->type == WORD)
			new_type = "WORD";
		else if (tmp->type == WHITE_SPACE)
			new_type = "WHITE_SPACE";
		else if (tmp->type == ENV)
			new_type = "ENV";
		else if (tmp->type == PIPE)
			new_type = "PIPE_LINE";
		else if (tmp->type == REDIR_IN)
			new_type = "REDIR_IN";
		else if (tmp->type == REDIR_OUT)
			new_type = "REDIR_OUT";
		else if (tmp->type == HERE_DOC)
			new_type = "HERE_DOC";
		else if (tmp->type == APPEND)
			new_type = "APPEND_OUT";
		else if (tmp->type == REDIR_HERE_DOC)
			new_type = "REDIR_HERE_DOC";
		else
			new_type = "WORD";
		space_left = 14 - ft_strlen(new_type);
		printf("|    %s", new_type);
		while (i < space_left)
		{
			printf(" ");
			i++;
		}
		printf("|\n");
		tmp = tmp->next;
	}
	printf("-------------------------------------------------------------------------------\n");
}

t_token	*parse_token(char *line)
{
	t_token	*token;
	t_token	*tmp;
	size_t	i;

	i = -1;
	token = (t_token *)malloc(sizeof(t_token));
	tmp = token;
	while (++i <= ft_strlen(line))
	{
		if (line[i] == ' ' || line[i] == '\0')
		{
			tmp->data = ft_substr(line, 0, i);
			get_token_state(tmp);
			get_token_type(tmp);
			line = line + i + 1;
			i = 0;
			tmp->next = (t_token *)malloc(sizeof(t_token));
			tmp = tmp->next;
			ft_bzero(tmp, sizeof(t_token));
		}
	}
	tmp->next = NULL;
	set_size(token);
	print_tokens(token);
	return (token);
}
