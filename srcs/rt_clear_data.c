/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_clear_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:09 by coverand          #+#    #+#             */
/*   Updated: 2022/06/22 15:21:31 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_clear(t_scene **scene)
{
	if ((*scene)->cams)
	{
		if ((*scene)->cams->direction)
			free((*scene)->cams->direction);
		if ((*scene)->cams->origin)
			free((*scene)->cams->origin);
		free((*scene)->cams);
	}
	if ((*scene)->ambient)
		free((*scene)->ambient);
	if ((*scene)->light)
	{
		if ((*scene)->light->point)
			free((*scene)->light->point);
		free((*scene)->light);
	}
}
