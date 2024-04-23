/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:35:48 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/04 16:44:09 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize < len_dst || dstsize == 0)
	{
		return (dstsize + len_src);
	}
	i = len_dst;
	while (i < dstsize - 1 && src[i - len_dst])
	{
		dst[i] = src[i - len_dst];
		i++;
	}
	dst[i] = '\0';
	return (len_dst + len_src);
}
