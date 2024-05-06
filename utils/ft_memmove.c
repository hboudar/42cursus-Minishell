/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:15:20 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/20 13:21:49 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_p;
	char	*src_p;

	dst_p = (char *)dst;
	src_p = (char *)src;
	if (dst_p < src_p)
		ft_memcpy(dst, src, len);
	else if (src_p < dst_p)
		while (len--)
			dst_p[len] = src_p[len];
	return (dst_p);
}
