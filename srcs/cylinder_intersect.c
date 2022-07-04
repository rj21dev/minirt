/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:34:41 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 15:45:17 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	check_dist(double *dist, t_cylinder cylinder, t_ray ray)
{
	t_v3	q;
	t_v3	p2;

	p2 = vec_add(cylinder.point, vec_mult(cylinder.or_vec, cylinder.height));
	q = vec_add(ray.origin, vec_mult(ray.direction, *dist));
	if (dot_prod(cylinder.or_vec, vec_sub(q, cylinder.point)) <= 0)
		*dist = -1;
	if (dot_prod(cylinder.or_vec, vec_sub(q, p2)) >= 0)
		*dist = -1;
}

static int	cyl_get_roots(double *d, t_cylinder cyl, t_ray ray)
{
	t_v3	a_sqrt;
	t_v3	right;
	double	a;
	double	b;
	double	c;

	a_sqrt = vec_sub(ray.direction, \
	vec_mult(cyl.or_vec, dot_prod(ray.direction, cyl.or_vec)));
	a = dot_prod(a_sqrt, a_sqrt);
	right = vec_sub(vec_sub(ray.origin, cyl.point), \
	vec_mult(cyl.or_vec, dot_prod(vec_sub(ray.origin, cyl.point), cyl.or_vec)));
	b = 2 * dot_prod(a_sqrt, right);
	c = dot_prod(right, right) - cyl.radius * cyl.radius;
	if (!solve_quadratic(new_abc(a, b, c), &d[0], &d[1]))
		return (0);
	return (1);
}

int	cylinder_intersect(t_ray ray, t_cylinder cylinder, double *dist)
{
	double	d[2];

	if (!cyl_get_roots(d, cylinder, ray))
		return (0);
	if (d[0] > 0)
		check_dist(&d[0], cylinder, ray);
	if (d[1] > 0)
		check_dist(&d[1], cylinder, ray);
	if (d[0] < 0 && d[1] < 0)
		return (0);
	if (d[1] < d[0])
		if (d[1] > 0)
			*dist = d[1];
	else
		*dist = d[0];
	else
	{
		if (d[0] > 0)
			*dist = d[0];
		else
			*dist = d[1];
	}
	return (1);
}
