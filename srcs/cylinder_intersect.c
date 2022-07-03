/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:34:41 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 00:55:06 by rjada            ###   ########.fr       */
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

	a_sqrt = vec_sub(ray.direction, vec_mult(cyl.or_vec, dot_prod(ray.direction, cyl.or_vec)));
	a = dot_prod(a_sqrt, a_sqrt);
	right = vec_sub(vec_sub(ray.origin, cyl.point), vec_mult(cyl.or_vec, dot_prod(vec_sub(ray.origin, cyl.point), cyl.or_vec)));
	b = 2 * dot_prod(a_sqrt, right);
	c = dot_prod(right, right) - cyl.radius * cyl.radius;
	if (!solve_quadratic(new_abc(a, b, c), &d[0], &d[1]))
		return (0);
	return (1);
}

// https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
/*
* ray - ray direction;
* 1) Find cam_cyl = ray origin - center point of shape
* 2) Find a, b, c coef:
	a   = D|D - (D|V)^2
	b/2 = D|X - (D|V)*(X|V)
	c   = X|X - (X|V)^2 - r*r
	
	D - the ray direction
	X - X equals O-C (ray origin - center point of shape)
	V - is a unit length vector that determines cylinder's axis
	r - is the cylinder's radius
*/
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
