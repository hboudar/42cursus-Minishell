/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:57:45 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/16 23:18:09 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len);
	result[len] = '\0';
	return (result);
}
