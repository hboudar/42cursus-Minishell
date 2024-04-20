/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:04:44 by hboudar           #+#    #+#             */
/*   Updated: 2023/11/17 00:50:37 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*res;

	if (!lst || !f || !del)
		return (NULL);
	result = NULL;
	while (lst)
	{
		res = ft_lstnew(NULL);
		if (!res)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		res->content = f(lst->content);
		ft_lstadd_back(&result, res);
		lst = lst->next;
	}
	return (result);
}
