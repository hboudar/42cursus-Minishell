/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 03:58:52 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/12 00:37:34 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_files(t_token **token, t_token *limit, char **files)
{
	int		i;
	t_token	*tmp;
	t_token	*new;

	tmp = *token;
	i = 0;
	while (tmp->next != limit)
		tmp = tmp->next;
	while (files[i])
	{
		new = (t_token *)malloc(sizeof(t_token));
		if (!new)
		{
			perror("malloc");
			exit(1);
		}
		ft_bzero(new, sizeof(t_token));
		new->data = ft_strdup(files[i]);
		new->type = WORD;
		new->state = GENERAL;
		new->next = tmp->next;
		tmp->next = new;
		tmp = new;
		i++;
	}
}

int	match(char *pattern, char *str)
{
	int	i;

	i = 0;
	while (pattern[i] != '*' && pattern[i])
	{
		if (pattern[i] != str[i])
			return (0);
		i++;
	}
	if (pattern[i] == '*' && str[i] && pattern[i + 1] == '\0')
		return (1);
	else if (!str[i])
		return (0);
	else
		return (match(pattern + i + 1, str + i));
}

char	**get_files(char *pattern)
{
	DIR				*dir;
	char			**files;
	struct dirent	*entry;

	dir = opendir(".");
	files = NULL;
	if (!dir)
	{
		perror("opendir");
		return (NULL);
	}
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match(pattern, entry->d_name))
			add_last(&files, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (files);
}

void	expand_wildcard(t_token **token)
{
	char	**files;
	t_token	*tmp;
	t_token	*tmp2;

	tmp = *token;
	files = NULL;
	while (tmp)
	{
		if (tmp->type == WILDCARD
			|| (tmp->state == GENERAL && ft_strchr(tmp->data, '*')))
		{
			files = get_files(tmp->data);
			if (!files)
			{
				tmp = tmp->next;
				continue ;
			}
			tmp2 = tmp->next;
			remove_token(token, tmp);
			add_files(token, tmp2, files);
			free_tab(&files);
			tmp = tmp2;
		}
		else
			tmp = tmp->next;
	}
}
