/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:32:17 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/26 09:49:07 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*src;
	char	*to_find;
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	else if (!haystack && !len)
		return (NULL);
	src = (char *)haystack;
	to_find = (char *)needle;
	i = 0;
	while (src[i] && i < len)
	{
		j = 0;
		if (src[i] == to_find[j])
		{
			while (src[i + j] == to_find[j] && i + j < len && src[i + j])
				j++;
			if (to_find[j] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
