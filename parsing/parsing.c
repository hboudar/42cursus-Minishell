/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/23 15:15:22 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_tablen(char **args)
{
	int	i;	
	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	free_tab(char **args)
{
    int	i;
    
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

t_token	*pipeless_token(t_token *token)
{
	t_token	*tmp;
	t_token	*tmp_new;
	t_token	*new_token;
	int		i;

	i = 0;
	tmp = token;
	new_token = (t_token *)malloc(sizeof(t_token));
	tmp_new = new_token;
	while (tmp->type != PIPE)
	{
		tmp_new->data = ft_strdup(tmp->data);
		tmp_new->type = tmp->type;
		tmp_new->state = tmp->state;
		tmp_new->next = (t_token *)malloc(sizeof(t_token));
		tmp_new = tmp_new->next;
		tmp = tmp->next;
		i++;
	}
	new_token->size = i;
	return (new_token);
}

void	get_cmd(t_cmd **cmd, t_token *token)
{
	int		i;
	int		j;
	t_token	*tmp;
	char	**args;

	i = 0;
	j = 0;
	args = (char **)malloc(sizeof(char *) * (token->size + 1));
	tmp = token;
	while (tmp)
	{
		if (has_pipe(token))
		{
			(*cmd)->type = PIPECMD;
			(*cmd)->left = (t_cmd *)malloc(sizeof(t_cmd));
			(*cmd)->right = (t_cmd *)malloc(sizeof(t_cmd));
			get_cmd(&(*cmd)->left, pipeless_token(token));
			while (tmp->type != PIPE)
			{
				tmp = tmp->next;
				i++;
			}
			get_cmd(&(*cmd)->right, tmp->next);
			break;
		}	
		else
		{
			(*cmd)->type = CMD;
			(*cmd)->state = tmp->state;
			args[j] = ft_strdup(tmp->data);
			j++;
		}
		tmp = tmp->next;
	}
	args[j] = NULL;
	(*cmd)->args = args;
	(*cmd)->size = j;
	free(token);
}

void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("%s ", tmp->data);
		tmp = tmp->next;
	}
}

t_cmd	*parse_line(char *line)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	token = parse_token(line);
	print_token(token);
	get_cmd(&cmd, token);
	return (cmd);
}
