/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:50:38 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/25 10:08:41 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	else if (!*s1)
		return (ft_strdup(""));
	start = 0;
	while (ft_strchr(set, s1[start]) != NULL && s1[start])
		start++;
	end = ft_strlen(s1) - 1;
	while (ft_strrchr(set, s1[end]) != NULL && end >= 0)
		end--;
	str = ft_substr(s1 + start, 0, (end - start) + 1);
	if (!str)
		return (NULL);
	return (str);
}
