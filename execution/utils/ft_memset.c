/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:39:39 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/26 09:44:30 by hboudar          ###   ########.fr       */
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
