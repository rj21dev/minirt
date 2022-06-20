/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:39 by rjada             #+#    #+#             */
/*   Updated: 2022/06/20 16:41:40 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere)
{
	float	b;
	float	c;
	float	discr;
	float	dist_1;
	// float	dist_2;
	t_vector	*cam_sphere;

	dist_1 = 0;
	// dist_2 = 0;
	cam_sphere = vec_substract(cam->origin, sphere->center);
	b = 2 * vec_dot_product(cam_sphere, ray);
	c = vec_dot_product(cam_sphere, cam_sphere) - sphere->radius * sphere->radius;
	discr = b * b - 4 * c;
	free(cam_sphere);
	if (discr < 0)
		return (0);
	dist_1 = b * (-1) - sqrt(discr) / 2;
	// dist_2 = b * (-1) + sqrt(discr) / 2;
	if (dist_1 > 0)
		return (1);
	//return (dist) float
	return (0);
}
