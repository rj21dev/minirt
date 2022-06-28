/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:39 by rjada             #+#    #+#             */
/*   Updated: 2022/06/28 11:53:09 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static float	min_f(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

void	sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere, float *dist)
{
	float		b;
	float		c;
	float		root_1;
	float		root_2;
	float		discr;
	t_vector	*cam_sphere;

	cam_sphere = vec_substract(cam->origin, sphere->center);
	b = 2 * vec_dot_product(cam_sphere, ray);
	c = vec_dot_product(cam_sphere, cam_sphere) - sphere->radius * sphere->radius;
	discr = b * b - 4 * c;
	free(cam_sphere);
	if (discr < 0)
	{
		*dist = _INFINITY;
		return ;
	}
	root_1 = (b * (-1) - sqrt(discr)) / 2;
	root_2 = (b * (-1) + sqrt(discr)) / 2;
	*dist = min_f(root_1, root_2);
}
