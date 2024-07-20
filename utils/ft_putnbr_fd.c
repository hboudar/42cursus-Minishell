/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:25:58 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 08:25:59 by aoulahra         ###   ########.fr       */
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
