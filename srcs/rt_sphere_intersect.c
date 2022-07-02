/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:39 by rjada             #+#    #+#             */
/*   Updated: 2022/07/02 10:54:30 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	min_f(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

void	sphere_intersect(t_ray ray, t_sphere *sphere, float *dist)
{
	float		b;
	float		c;
	// float		root_1;
	// float		root_2;
	float		discr;
	t_vector	l;

	l = vec_substract(ray.origin, sphere->center);
	b = 2 * vec_dot_product(ray.direction, l);
	c = vec_dot_product(l, l) - sphere->radius * sphere->radius;
	discr = b * b - 4 * c;
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
