/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 02:44:08 by hboudar           #+#    #+#             */
/*   Updated: 2024/05/22 16:52:28 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_list(t_list **list, int i, int l)
{
	t_list	*last_node;
	t_list	*red_node;
	char	*buf;

	buf = malloc(((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (1);
	red_node = malloc(sizeof(t_list));
	if (!red_node)
	{
		free(buf);
		buf = NULL;
		return (1);
	}
	last_node = ft_find_last_node(*list);
	while (last_node->content[i] && last_node->content[i] != '\n')
		++i;
	while (last_node->content[i] && last_node->content[++i])
		buf[l++] = last_node->content[i];
	buf[l] = '\0';
	red_node->content = buf;
	red_node->next = NULL;
	ft_free_all(list, &red_node, &buf);
	return (0);
}

char	*ft_get_line(t_list **list)
{
	char	*line;
	t_list	*tmp;

	if (!list || !*list)
		return (NULL);
	line = malloc(ft_len_to_newline(*list, 0, 0) + 1);
	if (line)
		ft_copy_str(*list, line, 0, 0);
	if (!line || ft_free_list(list, 0, 0))
	{
		while (*list != NULL)
		{
			tmp = (*list)->next;
			free((*list)->content);
			(*list)->content = NULL;
			free(*list);
			*list = NULL;
			*list = tmp;
		}
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}

int	ft_fill_list(t_list **list, char *buff)
{
	t_list	*last_node;

	if (!list || !*list)
	{
		last_node = malloc(sizeof(t_list));
		if (!last_node)
			return (1);
		last_node->content = buff;
		last_node->next = NULL;
		*list = last_node;
	}
	else
	{
		last_node = ft_find_last_node(*list);
		last_node->next = malloc(sizeof(t_list));
		if (!last_node->next)
			return (1);
		last_node->next->content = buff;
		last_node->next->next = NULL;
	}
	return (0);
}

int	ft_get_list(t_list **list, int fd, int bytes_read)
{
	char	*buff;

	while (!ft_lstchar(*list, 0))
	{
		buff = malloc(((size_t)BUFFER_SIZE + 1));
		if (!buff)
			return (1);
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buff);
			buff = NULL;
			return (bytes_read == -1);
		}
		buff[bytes_read] = '\0';
		if (ft_fill_list(list, buff))
		{
			free(buff);
			buff = NULL;
			return (1);
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
	{
		while (list != NULL)
		{
			tmp = list->next;
			(1) && (free(list->content), list->content = NULL);
			(1) && (free(list), list = NULL, list = tmp);
		}
		return (NULL);
	}
	if (ft_get_list(&list, fd, 0))
	{
		while (list != NULL)
		{
			tmp = list->next;
			(1) && (free(list->content), list->content = NULL);
			(1) && (free(list), list = NULL, list = tmp);
		}
	}
	return (ft_get_line(&list));
}
