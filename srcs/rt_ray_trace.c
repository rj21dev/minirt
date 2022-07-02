/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:46 by rjada             #+#    #+#             */
/*   Updated: 2022/07/02 11:03:36 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	ft_objects_intersect(t_ray ray, t_scene *scene, \
float *closer_dist, t_list **closer)
{
	t_list		*tmp;
	float		dist[2];
	void		*test;

	tmp = scene->elements;
	while (tmp)
	{
		test = tmp->content;
		if (tmp->obj_id == SPHERE)
			sphere_intersect(ray, (t_sphere *)test, dist);
		// if (tmp->obj_id == PLANE)
		// 	plane_intersect(scene->cams->origin, ray, (t_plane *)test, dist);
		// if (tmp->obj_id == CYL)
		// 	cylinder_intersect(scene->cams->origin, ray, ((t_cylinder *)test), dist);
		if (dist[0] > 1 && dist[0] < *closer_dist)
		{
			*closer_dist = dist[0];
			*closer = tmp;
		}
		if (dist[1] > 1 && dist[1] < *closer_dist)
		{
			*closer_dist = dist[1];
			*closer = tmp;
		}
		tmp = tmp->next;
	}
}
/*
int	check_shadow(t_vector origin, t_vector direction, t_scene *scene)
{
	t_list		*tmp;
	t_list		*closer;
	float		dist[2];
	void		*test;
	// float		closest;

	closer = NULL;
	// closest = INFINITY;
	tmp = scene->elements;
	while (tmp)
	{
		test = tmp->content;
		if (tmp->obj_id == SPHERE)
			sphere_intersect(origin, direction, (t_sphere *)test, dist);
		if (tmp->obj_id == PLANE)
			plane_intersect(origin, direction, (t_plane *)test, dist);
		if (tmp->obj_id == CYL)
			cylinder_intersect(origin, direction, ((t_cylinder *)test), dist);
		if (dist[0] >= 0.001f && dist[0] <= 1)
		{
			// closest = dist[0];
			closer = tmp;
		}
		if (dist[1] >= 0.001f && dist[1] <= 1)
		{
			// closest = dist[1];
			closer = tmp;

		}
		tmp = tmp->next;
	}
	// while (tmp)
	// {
	// 	test = tmp->content;
	// 	if (tmp->obj_id == SPHERE)
	// 		sphere_intersect(origin, direction, (t_sphere *)test, &dist);
	// 	if (tmp->obj_id == PLANE)
	// 		plane_intersect(origin, direction, (t_plane *)test, &dist);
	// 	if (tmp->obj_id == CYL)
	// 		cylinder_intersect(origin, direction, ((t_cylinder *)test), &dist);
	// 	if (dist > 0.001f && dist < 1)
	// 	{
	// 		closer = tmp;
	// 	}
	// 	tmp = tmp->next;
	// }
	if (closer)
		return (0);
	return (1);
}

static float compute_light(t_list *closer, float closer_dist, t_vector ray, t_scene *scene)
{
	t_vector point;
	t_vector normal;
	t_vector vec_l;
	t_vector vec_r;
	// t_vector view;
	float n_dot;
	float r_dot_v;
	float intensity;

	point = vec_add(scene->cams->origin, vec_mult(closer_dist, ray));
	if (closer->obj_id == 1)
		normal = vec_substract(((t_sphere *)(closer->content))->center, point);
	if (closer->obj_id == 2)
		normal = ((t_plane *)closer->content)->or_vec;
	if (closer->obj_id == 3)
		normal = ((t_cylinder *)closer->content)->or_vec;
	vec_normalize(&normal);
	vec_l = vec_substract(point, scene->light->point);
	intensity = 0;
	intensity += scene->ambient->lighting_ratio;
	// if (check_shadow(point, vec_l, scene))
	// 	return (intensity);
	n_dot = vec_dot_product(normal, vec_l);
	if (n_dot > 0)
		intensity += scene->light->brightness_ratio * n_dot / (vec_length(vec_l));
	vec_r = vec_substract(vec_mult(2 * vec_dot_product(normal, vec_l), normal), vec_l);
	// view = vec_mult(-1, ray);
	r_dot_v = vec_dot_product(vec_r, ray);
	if (r_dot_v > 0)
		intensity += scene->light->brightness_ratio * pow(r_dot_v / vec_length(vec_r), 500);
	return (intensity);
}*/

/*t_color2	color2_add(t_color2 a, t_color2 b)
{
	t_color2	rtn;

	rtn.red = fmin(a.red + b.red, 0.99);
	rtn.green = fmin(a.green + b.green, 0.99);
	rtn.blue = fmin(a.blue + b.blue, 0.99);
	return (rtn);
}

t_color2	color2_mult(t_color a, t_color2 b)
{
	t_color2	rtn;

	rtn.red = fmin(a.r * b.red, 1);
	rtn.green = fmin(a.g * b.green, 1);
	rtn.blue = fmin(a.b * b. blue, 1);
	return (rtn);
}

t_color2	color2_coeff(t_color a, double coeff)
{
	t_color2	rtn;

	rtn.red = fmin(a.r * coeff, 1);
	rtn.green = fmin(a.g * coeff, 1);
	rtn.blue = fmin(a.b * coeff, 1);
	return (rtn);
}

t_color2	shade(t_scene *scene, t_ray sent, t_object *closest_object, \
																double t_min)
{
	t_v3		hit_point;
	t_v3		hit_normal;
	t_color2	result;
	t_color2	addition;

	result = int_color(0);
	hit_point = v3_add(sent.origin, v3_multiply(sent.direction, t_min));
	hit_normal = get_normal(hit_point, closest_object);
	if (dot_product(sent.direction, hit_normal) > 0)
		hit_normal = substract(create_v3(0, 0, 0), v3_multiply(hit_normal, 1));
	addition = light_contribution(scene->light, \
				new_inter(hit_point, hit_normal, closest_object, sent), \
				*scene);
	result = color2_add(result, addition);
	ret*/

int	ray_trace(t_ray ray, t_scene *scene)
{
	float		closer_dist;
	float		intensity = 1;
	t_list		*closer;
	t_vector 	cols;
	int 		color;
	// t_color		closer_color;

	closer_dist = _INFINITY;
	closer = NULL;
	ft_objects_intersect(ray, scene, &closer_dist, &closer);
	if (!closer)
		return (BACKGROUND_COLOR);
/*	t_color2	result;
	t_color2	ambient_color;
	ambient_color = color2_coeff(scene->ambient->color, \
									scene->ambient->lighting_ratio);
	if (closer->obj_id == 1)
		closer_color =  ((t_sphere *)closer->content)->color_struct;
	if (closer->obj_id == 2)
		closer_color =  ((t_sphere *)closer->content)->color_struct;
	if (closer->obj_id == 3)
		closer_color =  ((t_sphere *)closer->content)->color_struct;
	result = color2_add(color2_mult(closer_color, ambient_color), \
									shade(scene, ray, closer, closer_dist));*/
	
	// intensity = compute_light(closer, closer_dist, ray, scene);
	if (closer->obj_id == 1)
		cols = col_mult(intensity, ((t_sphere *)closer->content)->color_struct);
	// if (closer->obj_id == 2)
	// 	cols = col_mult(intensity, ((t_plane *)closer->content)->color_struct);
	// if (closer->obj_id == 3)
	// 	cols = col_mult(intensity, ((t_cylinder *)closer->content)->color_struct);
	color = color_mixer(cols);
	return (color);
}
