/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:40:05 by coverand          #+#    #+#             */
/*   Updated: 2022/07/03 17:10:48 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	plane_intersect(t_ray ray, t_plane plane, double *dist)
{
	t_v3	oc;
	double	denom;

	denom = dot_prod(plane.or_vec, ray.direction);
	if (fabs(denom) > 1e-6)
	{
		oc = vec_sub(plane.point, ray.origin);
		*dist = dot_prod(oc, plane.or_vec) / denom;
		return (*dist >= 0);
	}
	return (0);
}
