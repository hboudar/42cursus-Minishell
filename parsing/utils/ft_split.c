/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:29:18 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/11 13:44:23 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		while (s[i] == c && s[i])
		{
			if (s[i + 1] == '\0')
				return (count);
			i++;
		}
		while (s[i] != c && s[i])
			i++;
		count++;
	}
	return (count);
}

static char	*find_start(char *s, char c, int i)
{
	if (i == 1)
	{
		while (*s == c && *s)
			s++;
	}
	else
	{
		while (*s != c && *s)
			s++;
	}
	return (s);
}

static size_t	count_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	if (!c)
		return (ft_strlen(s));
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static void	free_table(char **tab, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	char	*ptr;
	size_t	len_words;
	size_t	i;

	len_words = count_words(s, c);
	words = (char **) malloc (sizeof(char *) * (len_words + 1));
	if (!s || !words)
		return (NULL);
	i = -1;
	ptr = (char *)s;
	while (++i < len_words)
	{
		if (*ptr == c)
			ptr = find_start(ptr, c, (*ptr == c));
		words[i] = ft_substr(ptr, 0, count_len(ptr, c));
		if (words[i] == NULL)
		{
			free_table(words, i);
			return (NULL);
		}
		ptr = find_start(ptr, c, (*ptr == c));
	}
	words[i] = NULL;
	return (words);
}
