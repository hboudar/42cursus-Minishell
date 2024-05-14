/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:15:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/14 22:44:52 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	fix_quotes(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp)
	{
		 
	}
}

void	print_redirections(t_cmd *cmd)
{
	t_infile	*tmp_in;
	t_outfile	*tmp_out;
	char		**args;

	tmp_in = cmd->infile;
	tmp_out = cmd->outfile;
	args = cmd->limiter;
	while (tmp_in)
	{
		printf("infile: %s\n", tmp_in->data);
		tmp_in = tmp_in->next;
	}
	while (tmp_out)
	{
		printf("outfile: %s\n", tmp_out->data);
		tmp_out = tmp_out->next;
	}
	while (args)
	{
		printf("limiter: %s\n", *args);
		args++;
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
		args[j] = ft_strdup(tmp->data);
		j++;
		tmp = tmp->next;
	}
	args[j] = NULL;
	(*cmd)->type = CMD;
	(*cmd)->args = args;
	(*cmd)->size = j;
}

t_cmd	*parse_cmd(t_token *token, t_env *env)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	fill_redirections(cmd, token);
	print_redirections(cmd);
	exit(0);
	// fix_quotes(token);
	expand_env(token, env);
	get_cmd(&cmd, token);
	return (cmd);
}
