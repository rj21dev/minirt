/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:09 by coverand          #+#    #+#             */
/*   Updated: 2022/07/07 20:28:45 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_clear(t_scene **scene)
{
	t_list	*tmp;

	if (*scene)
	{
		if ((*scene)->cams)
			free((*scene)->cams);
		if ((*scene)->ambient)
			free((*scene)->ambient);
		if ((*scene)->light)
			free((*scene)->light);
		if ((*scene)->elements)
		{
			tmp = (*scene)->elements;
			while (tmp)
			{
				free(((t_object *)tmp->content)->ptr);
				tmp = tmp->next;
			}
			ft_lstclear(&((*scene)->elements), free);
		}
		free(*scene);
	}
}
