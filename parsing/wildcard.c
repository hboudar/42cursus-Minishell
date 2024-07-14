/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:27:16 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/14 09:37:54 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_files(t_token **token, t_token *limit, char **files)
{
	int		i;
	t_token	*tmp;
	t_token	*new;

	tmp = *token;
	i = 0;
	while (tmp && tmp->next != limit)
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
		(tmp) && (new->next = tmp->next);
		(tmp) && (tmp->next = new);
		(!(*token)) && (*token = new);
		tmp = new;
		i++;
	}
}

int match(const char *pattern, const char *str)
{
    while (*pattern)
    {
        if (*pattern == '*')
        {
            pattern++;
            if (!*pattern)
                return 1;
            while (*str)
            {
                if (match(pattern, str))
                    return 1;
                str++;
            }
            return (0);
        }
        else if (*pattern == *str)
        {
            pattern++;
            str++;
        }
        else
            return (0);
    }
    return (!*str);
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

	(1) && (tmp = *token, files = NULL);
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
