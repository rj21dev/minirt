/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:15:20 by rjada             #+#    #+#             */
/*   Updated: 2022/06/28 16:09:50 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*last;
	t_list	*node;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	last = NULL;
	while (lst)
	{
		node = ft_lstnew((*f)(lst->content), lst->obj_id);
		if (!node)
			if (new_list)
				ft_lstclear(&new_list, del);
		if (last)
			last->next = node;
		if (!new_list)
			new_list = node;
		last = node;
		lst = lst->next;
	}
	return (new_list);
}
