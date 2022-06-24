/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:39 by rjada             #+#    #+#             */
/*   Updated: 2022/06/24 18:46:57 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere, float *dist1, float *dist2)
{
	float		a;
	float		b;
	float		c;
	float		discr;
	t_vector	*cam_sphere;

	cam_sphere = vec_substract(cam->origin, sphere->center);
	a = vec_dot_product(ray, ray);
	b = 2 * vec_dot_product(cam_sphere, ray);
	c = vec_dot_product(cam_sphere, cam_sphere) - sphere->radius * sphere->radius;
	discr = b * b - 4 * c * a;
	free(cam_sphere);
	if (discr < 0)
	{
		*dist1 = _INFINITY;
		*dist2 = _INFINITY;
		return ;
	}
	*dist1 = (b * (-1) - sqrt(discr)) / 2 * a;
	*dist2 = (b * (-1) + sqrt(discr)) / 2 * a;
}
