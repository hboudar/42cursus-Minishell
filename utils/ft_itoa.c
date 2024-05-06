/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:36:38 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/20 22:24:52 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_len(long int nbr)
{
	size_t	len;

	len = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

static void	ft_fill(unsigned int nbr, char *number, size_t index)
{
	if (nbr > 9)
		ft_fill(nbr / 10, number, index - 1);
	number[index] = nbr % 10 + 48;
}

char	*ft_itoa(int n)
{
	size_t	len_nbr;
	size_t	index;
	char	*number;

	len_nbr = ft_count_len((long int)n);
	number = malloc(sizeof(char) * (len_nbr + 1));
	if (!number)
		return (NULL);
	index = 0;
	if (n < 0)
	{
		number[index++] = '-';
		ft_fill(n * -1, number, len_nbr - 1);
	}
	else
		ft_fill(n, number, len_nbr - 1);
	number[len_nbr] = '\0';
	return (number);
}
