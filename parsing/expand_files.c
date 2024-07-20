/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:10:08 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/20 16:33:24 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_par_files(t_cmd *cmd, t_file *file, t_limiter *limiter)
{
	while (file)
	{
		ft_fileaddback(&cmd->file,
			ft_newfile(file->args, file->type, file->quotes));
		file = file->next;
	}
	while (limiter)
	{
		add_limiter(&cmd->limiter, limiter->limit, limiter->quotes);
		limiter = limiter->next;
	}
}

void	join_limit(t_limiter *limiter)
{
	char		*limit;
	char		*tmplimit;
	t_data		*tmp;
	t_limiter	*tmp_limiter;

	tmp_limiter = limiter;
	while (tmp_limiter->next)
		tmp_limiter = tmp_limiter->next;
	tmp = tmp_limiter->args;
	limit = ft_strdup("");
	while (tmp)
	{
		tmplimit = ft_strdup(limit);
		free(limit);
		limit = ft_strjoin(tmplimit, tmp->arg);
		free(tmplimit);
		tmp = tmp->next;
	}
	tmp_limiter->limit = limit;
}

void	expand_file(t_file *file, t_env *env)
{
	int		i;
	char	*filetmp;
	char	*filename;
	t_data	*tmp;

	tmp = file->args;
	i = tmp->state * (tmp->state != IN_DQUOTES);
	while (tmp)
	{
		if (tmp->type != 3)
			expand_string(&tmp->arg, env, i, NULL);
		tmp = tmp->next;
	}
	tmp = file->args;
	filename = ft_strdup("");
	while (tmp)
	{
		filetmp = ft_strdup(filename);
		free(filename);
		filename = ft_strjoin(tmp->arg, filetmp);
		free(filetmp);
		tmp = tmp->next;
	}
	file->data = filename;
	expand_wildcard_file(file);
}
