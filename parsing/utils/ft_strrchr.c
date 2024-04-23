/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:56:42 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/04 17:16:43 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)str;
	i = ft_strlen(str);
	while (ptr[i] != (char )c)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	return (ptr + i);
}
