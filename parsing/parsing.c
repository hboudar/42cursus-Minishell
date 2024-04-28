/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/28 12:02:15 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->data);
		free(tmp);
	}
}

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
			break;
		}	
		else if (tmp->data)
		{
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

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*data;

	i = 0;
	j = 0;
	data = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			while (env[i][j] != '=')
				j++;
			data = ft_strdup(env[i] + j + 1);
			break;
		}
		i++;
	}
	return (data);
}

void	expand_env(t_token *token, char **env)
{
	t_token	*tmp;
	int		i;
	char	*data;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == ENV && tmp->state != IN_SQUOTES)
		{
			data = ft_getenv(tmp->data + 1, env);
			if (data)
			{
				free(tmp->data);
				tmp->data = data;
			}
		}
		tmp = tmp->next;
	}
}

t_cmd	*parse_line(char *line, char **g_env)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	token = parse_token(line);
	expand_env(token, g_env);
	get_cmd(&cmd, token);
	return (cmd);
}
