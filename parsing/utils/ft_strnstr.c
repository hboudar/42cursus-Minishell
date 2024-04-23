/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 09:36:08 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/04 09:55:45 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *stack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)stack);
	i = 0;
	while (stack[i] && i < len)
	{
		if (stack[i] == needle[0])
		{
			j = 0;
			while (stack[i + j] == needle[j] && needle[j] && i + j < len)
				j++;
			if (needle[j] == '\0')
				return ((char *)stack + i);
		}
		i++;
	}
	return (NULL);
}
