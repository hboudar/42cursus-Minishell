/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:04:58 by aoulahra          #+#    #+#             */
/*   Updated: 2024/06/09 02:26:47 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_multiple_expand(char *str)
{
    int		i;
    int		quotes;
    int		dquotes;

    i = 0;
    quotes = 0;
    dquotes = 0;
    while (str[i])
    {
        if (str[i] == '\'' && !dquotes)
            quotes = !quotes;
        if (str[i] == '\"' && !quotes)
            dquotes = !dquotes;
        if (str[i] == '$' && !quotes && !dquotes)
            return (1);
        i++;
    }
    return (0);
}

void	expand_here_doc(char **str, t_env *env, int expand)
{
	char    *tmp;
	char    *tmp2;

	if (!expand)
		return ;
    tmp2 = *str;
	if (has_multiple_expand(*str))
		handle_multiple_expands(str, env);
	else
	{
        while (*tmp2 && *tmp2 != '$')
            tmp2++;
		tmp = get_expanded_value(&tmp2, env);
        replace_string(str, tmp);
	}
}
