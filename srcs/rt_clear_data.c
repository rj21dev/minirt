/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_clear_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:09 by coverand          #+#    #+#             */
/*   Updated: 2022/07/03 19:03:44 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_clear(t_scene **scene)
{
	if (*scene)
	{
		if ((*scene)->cams)
			free((*scene)->cams);
		if ((*scene)->ambient)
			free((*scene)->ambient);
		if ((*scene)->light)
			free((*scene)->light);
		if ((*scene)->elements)
			ft_lstclear(&((*scene)->elements), free);
		free(*scene);
	}
}
