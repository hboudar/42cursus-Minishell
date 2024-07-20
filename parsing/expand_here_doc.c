/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 08:55:57 by aoulahra          #+#    #+#             */
/*   Updated: 2024/07/12 08:55:58 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_env_var(char **str, char *expand, int len, char *mode)
{
	char	*tmp;
	char	*new_str;
	char	*tmp2;

	(1) && (tmp = *str, new_str = ft_strdup(""));
	while (*tmp != '$' && *tmp)
	{
		new_str = ft_strjoin_char(new_str, *tmp);
		tmp++;
	}
	tmp2 = expand;
	while (*tmp2)
	{
		new_str = ft_strjoin_char(new_str, *tmp2);
		tmp2++;
	}
	tmp += len + 1;
	while (*tmp)
	{
		new_str = ft_strjoin_char(new_str, *tmp);
		tmp++;
	}
	if (*str != mode)
		free(*str);
	*str = new_str;
}

char	*get_to_expand(char **str)
{
	char	*to_expand;
	char	*tmp;

	tmp = *str;
	to_expand = ft_strdup("");
	while (*tmp && ft_isword(*tmp))
	{
		to_expand = ft_strjoin_char(to_expand, *tmp);
		tmp++;
	}
	*str = tmp;
	return (to_expand);
}

void	expand_string(char **str, t_env *env, int quotes, char *tmp2)
{
	char	*tmp;
	char	*expand;
	char	*to_expand;

	if (quotes == IN_SQUOTES || quotes == IN_DQUOTES || !*str)
		return ;
	(1) && (tmp = *str, expand = NULL, tmp2 = *str);
	while (tmp && *tmp)
	{
		if (*tmp == '$')
		{
			tmp++;
			to_expand = get_to_expand(&tmp);
			expand = get_expanded_value(&to_expand, env);
			if (!expand)
				expand = ft_strdup("");
			replace_env_var(&tmp2, expand, ft_strlen(to_expand), tmp2);
			if (!expand[0])
				free(expand);
			free(to_expand);
		}
		else
			tmp++;
	}
	(*str != tmp2) && (free(*str), *str = tmp2);
}
