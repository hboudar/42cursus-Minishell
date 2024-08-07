/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:16:31 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/19 10:40:14 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_exit_state(t_prompt *prompt, t_data *data)
{
	char	*tmp;

	tmp = ft_itoa(prompt->exit_state);
	if (data->arg)
		free(data->arg);
	data->arg = tmp;
}

void	fill_args(t_cmd *cmd, int i)
{
	int		quotes;
	char	**new_data;
	t_data	*data;

	new_data = malloc(sizeof(char *) * (i + 1));
	ft_bzero(new_data, sizeof(char *) * (i + 1));
	data = cmd->data;
	i = 0;
	quotes = GENERAL;
	while (data)
	{
		if (i == 0)
			quotes = data->state;
		new_data[i] = ft_strdup(data->arg);
		data = data->next;
		i++;
	}
	new_data[i] = NULL;
	if ((!new_data[0] || !new_data[0][0]) && quotes == GENERAL)
	{
		cmd->args = NULL;
		free_tab(&new_data);
	}
	else
		cmd->args = new_data;
}

void	get_cmd(t_cmd **cmd, t_token *token)
{
	t_data	*data;

	data = NULL;
	while (token)
	{
		if (data)
		{
			data->next = (t_data *)malloc(sizeof(t_data));
			data = data->next;
		}
		else
		{
			data = (t_data *)malloc(sizeof(t_data));
			(*cmd)->data = data;
		}
		ft_bzero(data, sizeof(t_data));
		data->arg = ft_strdup(token->data);
		data->joinable = token->joinable;
		data->type = token->type;
		data->state = token->state;
		token = token->next;
	}
}

void	get_args(t_cmd *cmd)
{
	int		i;
	char	*tmp;
	t_data	*data;
	t_data	*tmp_data;

	data = cmd->data;
	while (data)
	{
		if (data->next && data->joinable)
		{
			tmp = data->arg;
			data->arg = ft_strjoin(data->arg, data->next->arg);
			(1) && (free(tmp), tmp_data = data->next);
			if (!data->state && tmp_data->state)
				data->state = tmp_data->state;
			data->next = data->next->next;
			data->joinable = tmp_data->joinable;
			(1) && (free(tmp_data->arg), free(tmp_data), i = 0);
		}
		else
			data = data->next;
	}
	i = get_args_count(cmd->data);
	handle_expanded_wildcards(cmd, &i);
	fill_args(cmd, i);
}

t_cmd	*parse_cmd(t_prompt *prmpt, t_token **token)
{
	t_cmd		*cmd;
	t_file		*file;
	t_limiter	*limiter;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_bzero(cmd, sizeof(t_cmd));
	file = prmpt->file;
	limiter = prmpt->limiter;
	if (!prmpt->subshell)
		add_par_files(cmd, file, limiter);
	fill_redirections(cmd, *token);
	remove_redirections(token);
	get_cmd(&cmd, *token);
	fill_expand(cmd, *token);
	free_token(token);
	return (cmd);
}
