/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:14:20 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/04 12:00:54 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t len)
{
	size_t			i;
	unsigned char	*tmp;

	if (len == 0)
		return ;
	tmp = (unsigned char *) ptr;
	i = 0;
	while (i < len)
	{
		tmp[i] = 0;
		i++;
	}
}
