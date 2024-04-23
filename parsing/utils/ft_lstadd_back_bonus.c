/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoulahra <aoulahra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:16:49 by aoulahra          #+#    #+#             */
/*   Updated: 2023/11/11 13:57:54 by aoulahra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	if (lst && !(*lst))
	{
		*lst = new;
		new->next = NULL;
	}
	else if (lst)
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}
