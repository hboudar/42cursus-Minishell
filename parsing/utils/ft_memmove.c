/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:57:03 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/04 12:53:52 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;

	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if (src < dst)
	{
		while (len--)
		{
			tmp_dst[len] = tmp_src[len];
		}
	}
	if (src > dst)
	{
		dst = ft_memcpy(dst, src, len);
	}
	return (dst);
}
