/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:18:56 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/11 13:25:30 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size_s;
	size_t	len_substr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	size_s = ft_strlen(s);
	if ((size_s - start) >= len)
		len_substr = len;
	else
		len_substr = size_s - start;
	if (start >= size_s)
		len_substr = 0;
	substr = (char *) malloc (sizeof(char ) * len_substr + 1);
	if (!substr)
		return (NULL);
	while (i < len_substr)
	{
		substr[i] = (char )s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
