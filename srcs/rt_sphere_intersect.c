/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:39 by rjada             #+#    #+#             */
/*   Updated: 2022/06/30 18:12:54 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	min_f(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

void	sphere_intersect(t_vector *or, t_vector *dr, t_sphere *sphere, float *dist)
{
	float		b;
	float		c;
	// float		root_1;
	// float		root_2;
	float		discr;
	t_vector	*cam_sphere;

	cam_sphere = vec_substract(or, sphere->center);
	b = 2 * vec_dot_product(cam_sphere, dr);
	c = vec_dot_product(cam_sphere, cam_sphere) - sphere->radius * sphere->radius;
	discr = b * b - 4 * c;
	free(cam_sphere);
	if (discr < 0)
	{
		dist[0] = _INFINITY;
		dist[1] = _INFINITY;
		return ;
	}
	dist[0] = (b * (-1) - sqrt(discr)) / 2;
	dist[1] = (b * (-1) + sqrt(discr)) / 2;
	// *dist = min_f(root_1, root_2);
}
