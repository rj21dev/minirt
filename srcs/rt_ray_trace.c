/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:46 by rjada             #+#    #+#             */
/*   Updated: 2022/06/28 17:25:18 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	ft_objects_intersect(t_vector *ray, t_scene *scene, \
float *closer_dist, t_list **closer)
{
	t_list		*tmp;
	float		dist;
	void		*test;

	tmp = scene->elements;
	while (tmp)
	{
		test = tmp->content;
		if (tmp->obj_id == SPHERE)
			sphere_intersect(scene->cams, ray, (t_sphere *)test, &dist);
		if (tmp->obj_id == PLANE)
			plane_intersect(scene->cams, ray, (t_plane *)test, &dist);
		if (tmp->obj_id == CYL)
			cylinder_intersect(scene->cams, ray, ((t_cylinder *)test), &dist);
		if (dist > 1 && dist < *closer_dist)
		{
			*closer_dist = dist;
			*closer = tmp;
		}
		tmp = tmp->next;
	}
}

static float compute_light(t_list *closer, float closer_dist, t_vector *ray, t_scene *scene)
{
	t_vector *mult;
	t_vector *point;
	t_vector *normal;
	t_vector *vec_l;
	t_vector *vec_r;
	t_vector *view;
	float n_dot;
	float r_dot_v;
	float intensity;

	mult = vec_mult(closer_dist, ray);
	point = vec_add(scene->cams->origin, mult);
	if (closer->obj_id == 1)
		normal = vec_substract(((t_sphere *)(closer->content))->center, point);
	if (closer->obj_id == 2)
		normal = ((t_plane *)closer->content)->or_vec;
	if (closer->obj_id == 3)
		normal = ((t_cylinder *)closer->content)->or_vec;
	vec_normalize(normal);
	vec_l = vec_substract(scene->light->point, point);
	n_dot = vec_dot_product(normal, vec_l);
	intensity = 0;
	intensity += scene->ambient->lighting_ratio;
	if (n_dot > 0)
		intensity += scene->light->brightness_ratio * n_dot / vec_length(vec_l);
	vec_r = vec_substract(vec_mult(2 * vec_dot_product(normal, vec_l), normal), vec_l);
	view = vec_mult(-1, ray);
	r_dot_v = vec_dot_product(vec_r, view);
	if (r_dot_v > 0)
		intensity += scene->light->brightness_ratio * pow(r_dot_v / vec_length(vec_r), 50);
	return (intensity);
	free(mult);
	free(point);
	if (closer->obj_id == 1)
		free(normal);
	free(vec_l);
	free(vec_r);
	free(view);
}

int	ray_trace(t_vector *ray, t_scene *scene)
{
	float		closer_dist;
	float		intensity;
	t_list		*closer;
	t_vector 	*cols;
	int 		color;

	closer_dist = _INFINITY;
	closer = NULL;
	ft_objects_intersect(ray, scene, &closer_dist, &closer);
	if (!closer)
		return (BACKGROUND_COLOR);
	intensity = compute_light(closer, closer_dist, ray, scene);
	if (closer->obj_id == 1)
		cols = col_mult(intensity, ((t_sphere *)closer->content)->color_struct);
	if (closer->obj_id == 2)
		cols = col_mult(intensity, ((t_plane *)closer->content)->color_struct);
	if (closer->obj_id == 3)
		cols = col_mult(intensity, ((t_cylinder *)closer->content)->color_struct);
	color = color_mixer(cols);
	free(cols);
	return (color);
}
