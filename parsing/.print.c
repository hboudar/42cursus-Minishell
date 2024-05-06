/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .print.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:44:10 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/06 16:36:37 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_prompt(t_prompt *prompt)
{
	if (!prompt)
		return ;
	if (prompt->type == P_AND)
	{
		print_prompt(prompt->left);
		printf(" && " );
		print_prompt(prompt->right);
	}
	else if (prompt->type == P_OR)
	{
		print_prompt(prompt->left);
		printf(" || ");
		print_prompt(prompt->right);
	}
	else
		print_cmd(prompt->cmd);
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
		printf("|    %s", tmp->data);
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
			printf("|    GENERAL");
			break;
		case 1:
			printf("|    ENVIROMENT");
			break;
		case 2:
			printf("|    INFILE");
			break;
		case 3:
			printf("|    OUTFILE");
			break;
		case 4:
			printf("|    IN_SQUOTE");
			break;
		case 5:
			printf("|    IN_DQUOTE");
			break;
		case 6:
			printf("|    LIMITER");
			break;
		}
		switch (tmp->state)
		{
		case 0:
			space_left = 14 - 8;
			break;
		
		case 1:
			space_left = 14 - 11;
			break;
		case 2:
			space_left = 14 - 7;
			break;
		case 3:
			space_left = 14 - 8;
			break;
		case 4:
			space_left = 14 - 10;
			break;
		case 5:
			space_left = 14 - 10;
			break;
		case 6:
			space_left = 14 - 7;
			break;
		}
		while (i < space_left)
		{
			printf(" ");
			i++;
		}
		i = 0;
		char *new_type;
		if (tmp->type == WORD)
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
		else if (tmp->type == OPENPAR)
			new_type = "OPEN_PAR";
		else if (tmp->type == CLOSEPAR)
			new_type = "CLOSE_PAR";
		else if (tmp->type == AND_TOKEN)
			new_type = "AND";
		else if (tmp->type == OR_TOKEN)
			new_type = "OR";
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