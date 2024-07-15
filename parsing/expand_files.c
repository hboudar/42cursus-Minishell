/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:10:08 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/15 16:00:42 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_limit(t_limiter *limiter)
{
	char	*limit;
	char	*tmplimit;
	t_data	*tmp;

	tmp = limiter->args;
	limit = ft_strdup("");
	while (tmp)
	{
		tmplimit = ft_strdup(limit);
		free(limit);
		limit = ft_strjoin(tmplimit, tmp->arg);
		free(tmplimit);
		tmp = tmp->next;
	}
	limiter->limit = limit;
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
		printf("arg: %s\n", tmp->arg);
		filetmp = ft_strdup(filename);
		free(filename);
		filename = ft_strjoin(tmp->arg, filetmp);
		free(filetmp);
		tmp = tmp->next;
	}
	file->data = filename;
}
