/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 00:04:28 by rjada             #+#    #+#             */
/*   Updated: 2022/07/04 00:20:00 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static double	spec_coeff(t_light *light, t_inter inter)
{
	t_v3	l_vec;
	t_v3	r_vec;
	t_v3	pre_r_vec;
	t_v3	bv_vec;
	double	result;

	l_vec = vec_sub(light->point, inter.hit_p);
	vec_norm(&l_vec);
	pre_r_vec = vec_mult(inter.hit_n, dot_prod(l_vec, inter.hit_n));
	r_vec = vec_add(l_vec, vec_mult(pre_r_vec, -2));
	bv_vec = vec_sub(inter.hit_p, inter.ray.origin);
	vec_norm(&bv_vec);
	result = fmax(dot_prod(r_vec, bv_vec), 0);
	result = pow(result, 10);
	return (result);
}

static t_color2	calc_specular(t_light *light, t_inter inter)
{
	t_color2	specular;
	t_color2	highlight;
	double		coeff;

	highlight.red = 1;
	highlight.green = 1;
	highlight.blue = 1;
	highlight = color2_coeff(highlight, (1 - METALNESS));
	specular = color2_add(color2_coeff(inter.closest->color, METALNESS), highlight);
	coeff = spec_coeff(light, inter);
	return (color2_coeff(specular, coeff));
}

static t_inter	new_inter(t_v3 hit_p, t_v3 hit_n, t_object *closest, t_ray ray)
{
	t_inter	inter;

	inter.hit_p = hit_p;
	inter.hit_n = hit_n;
	inter.closest = closest;
	inter.ray = ray;
	return (inter);
}

static t_color2	calc_shadows(t_light *light, t_inter inter, t_scene scene)
{
	t_object	*closest;
	double		dist;
	t_v3		l_direction;
	t_ray		lray;
	double		coeff;
	double		len_to_obj;
	t_color2	light_color;
	t_color2	object_color;
	t_color2	total;

	coeff = 0;
	l_direction = vec_sub(light->point, inter.hit_p);
	vec_norm(&l_direction);
	lray = create_ray(vec_add(inter.hit_p, vec_mult(inter.hit_n, 0.1)), l_direction);
	len_to_obj = vec_len(vec_sub(light->point, inter.hit_p));
	if (!intersect_all(scene.elements, lray, &closest, &dist) || dist > len_to_obj)
		coeff = fmax(0, dot_prod(inter.hit_n, l_direction));
	light_color = color2_coeff(light->color, light->intensity);
	object_color = inter.closest->color;
	total = color2_coeff(color2_mult(light_color, object_color), coeff);
	if (coeff)
		total = color2_add(total, calc_specular(light, inter));
	return (total);
}

t_color2	calc_light(t_scene *scene, t_ray ray, t_object *closest, double d_min)
{
	t_v3		hit_p;
	t_v3		hit_n;
	t_color2	result;
	t_color2	shadows;

	result = int_color(0);
	hit_p = vec_add(ray.origin, vec_mult(ray.direction, d_min));
	hit_n = get_normal(hit_p, closest);
	if (dot_prod(ray.direction, hit_n) > 0)
		hit_n = vec_sub(new_v3(0, 0, 0), vec_mult(hit_n, 1));
	shadows = calc_shadows(scene->light, new_inter(hit_p, hit_n, closest, ray), *scene);
	result = color2_add(result, shadows);
	return (result);
}
