/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:28:12 by aoulahra          #+#    #+#             */
/*   Updated: 2024/04/28 12:10:58 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_substr_trim(char *s, unsigned int start, size_t len)
{
	if (s[start] == '(')
		return (ft_substr(s, start + 1, len - 2));
	return (ft_substr(s, start, len));
}

t_prompt	*parse_prompt(char *line, char **env)
{
	t_prompt	*prmpt;
	int			i;

	i = 0;
	prmpt = (t_prompt *)malloc(sizeof(t_prompt));
	if (line[i] == '(')
		while (line[i] != ')' || line[i] != '\0')
			i++;
	while (line[i] == ' ')
		i++;
	if (line[i] && line[i] == '&' && line[i + 1] == '&')
	{
		prmpt->type = AND;
		prmpt->left = parse_prompt(ft_substr_trim(line, 0, i), env);
		prmpt->right = parse_prompt(ft_substr_trim(line, i + 2, ft_strlen(line) - i - 2), env);
	}
	else if (line[i] && line[i] == '|' && line[i + 1] == '|')
	{
		prmpt->type = OR;
		prmpt->left = parse_prompt(ft_substr_trim(line, 0, i), env);
		prmpt->right = parse_prompt(ft_substr_trim(line, i + 2, ft_strlen(line) - i - 2), env);
	}
	else
	{
		prmpt->type = NONE;
		prmpt->cmd = parse_line(line + i, env);
	}
	return (prmpt);
}
