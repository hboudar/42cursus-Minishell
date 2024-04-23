/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:22:54 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/11 13:33:26 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const *set, char const c)
{
	size_t	i;

	i = 0;
	while (set[i] != c && set[i])
		i++;
	return (set[i] == c);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	strt;
	size_t	end;
	size_t	len_trim;
	char	*trimmed;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	strt = 0;
	end = ft_strlen(s1);
	while (s1[strt] && check(set, s1[strt]))
		strt++;
	while (end > strt && check(set, s1[end - 1]))
		end--;
	if (end <= strt)
		len_trim = 0;
	else
		len_trim = end - strt;
	trimmed = ft_substr(s1, strt, len_trim);
	return (trimmed);
}
