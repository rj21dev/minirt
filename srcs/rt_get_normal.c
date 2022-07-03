/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_obj_normal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:17:36 by rjada             #+#    #+#             */
/*   Updated: 2022/07/03 18:02:11 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_v3	get_plane_normal(t_plane plane)
{
	return (plane.or_vec);
}

static t_v3	get_cylinder_normal(t_v3 point, t_cylinder cylinder)
{
	t_v3	ctp;
	t_v3	normal;

	ctp = vec_sub(point, cylinder.point);
	normal = vec_sub(ctp, \
						vec_mult(cylinder.or_vec, \
									dot_prod(cylinder.or_vec, ctp)));
	vec_norm(&normal);
	return (normal);
}

static t_v3	get_sphere_normal(t_v3 point, t_sphere sphere)
{
	t_v3	rtn;

	rtn = vec_sub(point, sphere.center);
	vec_norm(&rtn);
	return (rtn);
}

t_v3	get_normal(t_v3 point, t_object *object)
{
	if (object->type == SPHERE)
		return (get_sphere_normal(point, *(t_sphere *)object->ptr));
	else if (object->type == PLANE)
		return (get_plane_normal(*(t_plane *)object->ptr));
	else
		return (get_cylinder_normal(point, *(t_cylinder *)object->ptr));
}
