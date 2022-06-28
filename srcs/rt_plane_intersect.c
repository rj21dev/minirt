/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:40:05 by coverand          #+#    #+#             */
/*   Updated: 2022/06/28 11:52:42 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	plane_intersect(t_camera *cam, t_vector *ray, \
t_plane *plane, float *dist)
{
	t_vector	*oc;
	float		denom;	

	denom = (vec_dot_product(ray, plane->or_vec));
	if (denom == 0)
	{
		*dist = _INFINITY;
		return ;
	}
	oc = vec_substract(cam->origin, plane->point);
	*dist = -(vec_dot_product(oc, plane->or_vec)) / denom;
}
