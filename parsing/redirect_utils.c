/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:07:32 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/14 22:49:20 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**add_last(char **file, char *data)
{
	char	**tmp;
	int        i;
	
	if (!file || !*file)
	{
		tmp = (char **)malloc(2);
		*tmp = data;
        *(tmp + 1) = NULL;
	}
	else
	{
		i = count_files(file);
		tmp = (char **)malloc(sizeof(char) * (i + 2));
		i = 0;
		while (file[i])
		{
			tmp[i] = ft_strdup(file[i]);
			i++;
		}
		tmp[i] = data;
		tmp[i + 1] = NULL;
		free_tab(file);
	}
	return (tmp);
}

t_infile    *ft_newinfile(char *data)
{
    t_infile	*new;

    new = (t_infile *)malloc(sizeof(t_infile));
    new->data = data;
    new->next = NULL;
    return (new);
}

t_outfile    *ft_newoutfile(char *data)
{
    t_outfile	*new;

    new = (t_outfile *)malloc(sizeof(t_outfile));
    new->data = data;
    new->next = NULL;
    return (new);
}

void	ft_infileaddback(t_infile **infile, t_infile *new)
{
    t_infile	*tmp;

    if (!*infile)
    {
        *infile = new;
        return ;
    }
    tmp = *infile;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

void	ft_outfileaddback(t_outfile **outfile, t_outfile *new)
{
    t_outfile	*tmp;

    if (!*outfile)
    {
        *outfile = new;
        return ;
    }
    tmp = *outfile;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
