/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:40:05 by coverand          #+#    #+#             */
/*   Updated: 2022/06/27 14:18:53 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	plane_intersect(t_camera *cam, t_vector *ray, \
t_plane *plane, float *dist)
{
	t_vector	*oc;
	float		denom;	

	dist[1] = _INFINITY;
	denom = (vec_dot_product(ray, plane->or_vec));
	if (denom == 0)
	{
		dist[0] = _INFINITY;
		return ;
	}
	oc = vec_substract(cam->origin, plane->point);
	dist[0] = -(vec_dot_product(oc, plane->or_vec)) / denom;
}
