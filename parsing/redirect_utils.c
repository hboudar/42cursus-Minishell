/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:07:32 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/14 23:10:39 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void    add_last(char ***file, char *data)
{
	int		i;
	char	**new;

	i = 0;
	if (!*file)
	{
		new = (char **)malloc(sizeof(char *) * 2);
		new[0] = data;
		new[1] = NULL;
		*file = new;
		return ;
	}
	i = count_files(*file);
	new = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*file)[i])
	{
		new[i] = ft_strdup((*file)[i]);
		i++;
	}
	new[i] = data;
	new[i + 1] = NULL;
	free_tab(*file);
	*file = new;
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
