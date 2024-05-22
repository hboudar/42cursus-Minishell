/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 02:44:36 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/22 16:52:13 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstchar(t_list *list, int i)
{
	while (list != NULL)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	ft_copy_str(t_list *list, char *str, int i, int k)
{
	while (list != NULL)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[k++] = '\n';
				str[k] = '\0';
				return ;
			}
			str[k++] = list->content[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
}

int	ft_len_to_newline(t_list *list, int len, int i)
{
	while (list != NULL)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	ft_free_all(t_list **list, t_list **clean_node, char **buf)
{
	t_list	*tmp;

	if (!list && !*list)
		return ;
	while (*list != NULL)
	{
		tmp = (*list)->next;
		free((*list)->content);
		(*list)->content = NULL;
		free(*list);
		*list = NULL;
		*list = tmp;
	}
	if ((*clean_node)->content[0])
		*list = *clean_node;
	else
	{
		free(*buf);
		*buf = NULL;
		free(*clean_node);
		*clean_node = NULL;
	}
}

t_list	*ft_find_last_node(t_list *list)
{
	while (list != NULL && list->next != NULL)
		list = list->next;
	return (list);
}
