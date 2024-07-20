/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:21:05 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 08:21:06 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_p;
	char	*src_p;

	if (!src && !dst)
		return (NULL);
	dst_p = (char *)dst;
	src_p = (char *)src;
	while (n > 0 && src_p != dst_p)
	{
		*dst_p = *src_p;
		dst_p++;
		src_p++;
		n--;
	}
	return (dst);
}
