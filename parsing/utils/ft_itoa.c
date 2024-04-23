/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:16:15 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/07 12:40:44 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_num(long int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len = 1;
	}
	while (n > 9)
	{
		len++;
		n = n / 10;
	}
	return (len + 1);
}

static void	fill_array(char *arr, long int n, int len)
{
	arr[len] = '\0';
	len--;
	if (n < 0)
	{
		arr[0] = '-';
		n = -n;
	}
	while (n > 9 && len > 0)
	{
		arr[len] = (char )(n % 10 + 48);
		n = n / 10;
		len--;
	}
	arr[len] = (char )(n + 48);
}

char	*ft_itoa(int n)
{
	int			array_len;
	char		*arr;
	long int	num;

	num = n;
	array_len = count_num(num);
	arr = (char *) malloc ((array_len + 1) * sizeof(char ));
	if (!arr)
		return (NULL);
	fill_array(arr, num, array_len);
	return (arr);
}
