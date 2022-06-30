/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:40:05 by coverand          #+#    #+#             */
/*   Updated: 2022/06/30 16:57:16 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	plane_intersect(t_vector *or, t_vector *ray, \
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
	oc = vec_substract(or, plane->point);
	*dist = -(vec_dot_product(oc, plane->or_vec)) / denom;
	free(oc);
}
