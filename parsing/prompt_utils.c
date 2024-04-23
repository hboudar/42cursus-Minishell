/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:28:12 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/22 15:42:35 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_prompt	*parse_prompt(char *line)
{
	t_prompt	*prmpt;
	char		**args;
	int			i;

	i = 0;
	prmpt = (t_prompt *)malloc(sizeof(t_prompt));
	args = ft_split_prompt(line, "&&", "||");
	while(args[i])
	{
		prmpt->cmd = parse_line(args[i]);
		i++;
	}
	return (prmpt);
}

size_t	ft_prmptlen(char *line)
{
	size_t	len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '&' && line[i + 1] == '&')
			len++;
		if (line[i] == '|' && line[i + 1] == '|')
			len++;
		i++;
	}
	return (len);
}

char	**ft_split_prompt(char *line, char *sep1, char *sep2)
{
	char	**args;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	args = (char **)malloc(sizeof(char *) * (ft_prmptlen(line) + 1));
	while (line[i])
	{
		if ((line[i] == sep1[j] && line[i + 1] == sep1[j + 1])
			|| (line[i] == sep2[j] && line[i + 1] == sep2[j + 1]))
		{
			args[k] = ft_substr(line, 0, i);
			line = line + i + 2;
			i = 0;
			k++;
		}
		i++;
	}
	args[k] = ft_strdup(line);
	args[k + 1] = NULL;
	return (args);
}

