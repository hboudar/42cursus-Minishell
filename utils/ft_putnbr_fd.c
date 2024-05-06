/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:59:09 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/12 18:42:53 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_devnbr(unsigned int nbr, int fd)
{
	if (nbr > 9)
		ft_devnbr(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + 48, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_devnbr(-n, fd);
	}
	else
		ft_devnbr(n, fd);
}
