/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:22:11 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 08:22:14 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*s_p;
	size_t			i;

	i = 0;
	s_p = (unsigned char *)s;
	while (len > i)
	{
		s_p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
