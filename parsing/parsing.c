/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/02 10:27:59 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	get_cmd(t_cmd **cmd, t_token *token)
{
	int		i;
	int		j;
	char	**args;
	t_token	*tmp;

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
			break ;
		}
		else if (tmp->data)
		{
			if (ft_strncmp(tmp->data, "$", 2) == 0)
				tmp = tmp->next;
			(*cmd)->type = CMD;
			args[j] = ft_strdup(tmp->data);
			j++;
		}
		tmp = tmp->next;
	}
	args[j] = NULL;
	(*cmd)->args = args;
	(*cmd)->size = j;
}

t_cmd	*parse_line(char *line, t_env *env)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	token = parse_token(line);
	expand_env(token, env);
	get_cmd(&cmd, token);
	return (cmd);
}
