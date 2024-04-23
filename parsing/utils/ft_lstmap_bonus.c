/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:37:43 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/07 14:17:56 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*ptr_new;

	if (del && f && lst)
	{
		ptr_new = NULL;
		while (lst)
		{
			new_lst = ft_lstnew(NULL);
			if (!new_lst)
			{
				ft_lstclear(&ptr_new, del);
				return (NULL);
			}
			new_lst->content = f(lst->content);
			ft_lstadd_back(&ptr_new, new_lst);
			lst = lst->next;
		}
		return (ptr_new);
	}
	return (NULL);
}
