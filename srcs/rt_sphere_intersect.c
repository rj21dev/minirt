/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere_intersect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:39 by rjada             #+#    #+#             */
/*   Updated: 2022/07/03 17:05:09 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	get_roots(double *t0, double *t1, t_ray ray, t_sphere sphere)
{
	t_v3	l;
	double	a;
	double	b;
	double	c;

	l = vec_sub(ray.origin, sphere.center);
	a = dot_prod(ray.direction, ray.direction);
	b = 2.0 * dot_prod(ray.direction, l);
	c = dot_prod(l, l) - sphere.radius * sphere.radius;
	if (solve_quadratic(new_abc(a, b, c), t0, t1) == 0)
		return (0);
	return (1);
}

int	sphere_intersect(t_ray ray, t_sphere sphere, double *dist)
{
	double	root_1;
	double	root_2;

	if (get_roots(&root_1, &root_2, ray, sphere) == 0)
		return (0);
	if (root_1 < 0)
	{
		root_1 = root_2;
		if (root_1 < 0)
			return (0);
	}
	*dist = root_1;
	return (1);
}
