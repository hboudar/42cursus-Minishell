/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:40:38 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/30 10:52:55 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	n;
	unsigned long	n_ll;
	int				sign;
	int				i;

	i = 0;
	while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	n_ll = 0;
	n = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + str[i] - 48;
		if (n / 10 != n_ll)
			return (-1);
		n_ll = n;
		i++;
	}
	return (n * sign);
}
