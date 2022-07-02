/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 23:06:57 by rjada             #+#    #+#             */
/*   Updated: 2022/07/02 11:31:32 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_ray	new_ray(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vector	get_direction(int x, int y, t_scene *scene)
{
	float	fov_coeff;
	float	aspect_ratio;
	float	p_x;
	float	p_y;

	fov_coeff = tan(scene->cams->fov / 2 * M_PI / 180);
	aspect_ratio = scene->width / scene->height;
	p_x = (2 * (x + 0.5) / scene->width - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / scene->height) * fov_coeff;
	return (new_vector(p_x, p_y, 1));
}

t_ray	ray_to_pixel(int x, int y, t_scene *scene)
{
	t_vector	origin;
	t_vector	direction;
	t_matrix	matrix;

	matrix = look_at(scene->cams->origin, scene->cams->direction);
	origin = mult_by_matrix(new_vector(0, 0, 0), matrix);
	direction = get_direction(x, y, scene);
	direction = mult_by_matrix(direction, matrix);
	direction = vec_substract(direction, origin);
	vec_normalize(&direction);
	return (new_ray(origin, direction));
}
