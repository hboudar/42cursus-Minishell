/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 22:24:03 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/27 23:37:13 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	ft_tablen(char **args)
{
	int	i;	
	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	free_tab(char **args)
{
    int	i;
    
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

char    **ft_tabdup(char **args)
{
    int	i;
    char	**new_args;
    
    i = 0;
    new_args = (char **)malloc(sizeof(char *) * (ft_tablen(args) + 1));
    while (args[i])
    {
        new_args[i] = ft_strdup(args[i]);
        i++;
    }
    new_args[i] = NULL;
    return (new_args);
}
