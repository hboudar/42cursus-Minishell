/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:59:05 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/25 12:25:05 by hboudar          ###   ########.fr       */
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
