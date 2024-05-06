/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:21:03 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/18 20:20:28 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char *str, char c)
{
	size_t	words;

	if (!str)
		return (-1);
	words = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str)
			words++;
		while (*str != c && *str)
			str++;
	}
	return (words);
}

static size_t	ft_word_size(char *str, char c)
{
	size_t	len_w;

	len_w = 0;
	while (str[len_w] && str[len_w] != c)
		len_w++;
	return (len_w);
}

static size_t	ft_seprun(char *str, char c)
{
	size_t	len_sep;

	len_sep = 0;
	while (str[len_sep] && str[len_sep] == c)
		len_sep++;
	return (len_sep);
}

static void	ft_free(char **split, size_t index)
{
	while (index--)
	{
		free(split[index]);
		split[index] = NULL;
	}
	free(split);
	split = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	*str;
	size_t	word_i;

	str = (char *)s;
	word_i = -1;
	split = (char **)malloc(sizeof(char *) * (ft_count_words(str, c) + 1));
	if (!s || !split)
		return (NULL);
	while (*str)
	{
		str += ft_seprun(str, c);
		if (*str)
		{
			split[++word_i] = ft_substr(str, 0, ft_word_size(str, c));
			if (!split[word_i])
			{
				ft_free(split, word_i);
				return (NULL);
			}
		}
		str += ft_word_size(str, c);
	}
	split[++word_i] = 0;
	return (split);
}
