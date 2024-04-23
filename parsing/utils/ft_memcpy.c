/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 09:40:08 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/04 12:42:56 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	i = 0;
	while (i < len && tmp_src != tmp_dst)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (dst);
}
