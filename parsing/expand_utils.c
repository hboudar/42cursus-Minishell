/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:21:20 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/02 14:20:45 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_count_expand(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			i++;
		else
		{
			count++;
			while (str[i] && !ft_is_whitespace(str[i]))
				i++;
		}
	}
return (count);
}

char	**ft_split_expand(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**newtab;

    if (!str)
        return (NULL);
	newtab = malloc(sizeof(char *) * (ft_count_expand(str) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]))
			i++;
		else
		{
			k = i;
			while (str[i] && !ft_is_whitespace(str[i]))
				i++;
			newtab[j] = ft_substr(str, k, i - k);
			j++;
		}
	}
	newtab[j] = NULL;
	return (newtab);
}
