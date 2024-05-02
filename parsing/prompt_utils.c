/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:28:12 by aoulahra          #+#    #+#             */
/*   Updated: 2024/05/02 10:37:36 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_substr_trim(char *s, unsigned int start, size_t len)
{
	while (s[start] && ((s[start] <= 13 && s[start] >= 9) || s[start] == 32))
		start++;
	if (s[start] == '(')
		return (ft_substr(s, start + 1, len - 2));
	return (ft_substr(s, start, len));
}

void	ft_hasparanthese(t_prompt *prmpt, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	prmpt->hasparanthese = 0;
	while (line[i] && j != 0 && !(line[i] == '&' && line[i + 1] == '&')
		&& !(line[i] == '|' && line[i + 1] == '|'))
	{
		if (line[i] == '(')
		{
			(j == -1) && (j = 0);
			(j == 0) && (prmpt->openpar = i + 1);
			prmpt->hasparanthese = 1;
			j++;
		}
		if (line[i] == ')' && j != -1)
		{
			j--;
			(j == 0) && (prmpt->closepar = i);
		}
		i++;
	}
	if (!prmpt->hasparanthese)
		prmpt->closepar = i;
}

int	check_and_or(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (line[i] && j)
	{
		if (line[i] == '(')
		{
			j = 1;
			while (line[++i] && j)
			{
				if (line[i] == '(')
					j++;
				if (line[i] == ')')
					j--;
			}
		}
		if ((line[i] == '&' && line[i + 1] == '&')
			|| (line[i] == '|' && line[i + 1] == '|'))
			return (0);
		i++;
	}
	return (1);
}

void	fix_line(t_prompt *prmpt, char **line)
{
	if (check_and_or(*line))
		return ;
	if (prmpt->hasparanthese)
		*line = *line + prmpt->closepar;
	while (**line && **line != '&' && **line != '|')
		(*line)++;
	*line += 2;
	if (prmpt->hasparanthese)
		*line = ft_strtrim(*line, ")");
}

int	is_and(char *line, t_prompt *prmpt)
{
	int	i;

	i = 0;
	if (prmpt->hasparanthese)
		*line = *line + prmpt->closepar;
	while (line[i])
	{
		if (line[i] == '&' && line[i + 1] == '&')
			return (1);
		i++;
	}
	return (0);
}

int	is_or(char *line, t_prompt *prmpt)
{
	int	i;

	i = 0;
	if (prmpt->hasparanthese)
		*line = *line + prmpt->closepar;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

t_prompt	*parse_prompt(char *line, t_env *env)
{
	int			i;
	t_prompt	*prmpt;

	(1) && (i = 0, prmpt = (t_prompt *)malloc(sizeof(t_prompt)));
	ft_hasparanthese(prmpt, line);
	if (check_and_or(line))
	{
		prmpt->type = NONE;
		prmpt->cmd = parse_line(ft_substr_trim(line, 0, ft_strlen(line)), env);
	}
	else if (is_and(line, prmpt))
	{
		prmpt->type = AND;
		prmpt->left = parse_prompt(ft_substr_trim(line, prmpt->openpar, prmpt->closepar - prmpt->openpar), env);
		fix_line(prmpt, &line);
		prmpt->right = parse_prompt(ft_substr_trim(line, 0, ft_strlen(line)), env);
	}
	else if (is_or(line, prmpt))
	{
		prmpt->type = OR;
		prmpt->left = parse_prompt(ft_substr_trim(line, prmpt->openpar, prmpt->closepar - prmpt->openpar), env);
		fix_line(prmpt, &line);
		prmpt->right = parse_prompt(ft_substr_trim(line, 0, ft_strlen(line)), env);
	}
	return (prmpt);
}
