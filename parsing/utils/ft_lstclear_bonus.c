/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:53:27 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/11 14:00:09 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_list;

	if (lst && *lst)
	{
		while ((*lst)->next)
		{
			next_list = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = next_list;
		}
		ft_lstdelone(*lst, del);
		*lst = NULL;
	}
}
