/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:46 by rjada             #+#    #+#             */
/*   Updated: 2022/06/30 19:46:43 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	ft_objects_intersect(t_vector *ray, t_scene *scene, \
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
			sphere_intersect(scene->cams->origin, ray, (t_sphere *)test, dist);
		if (tmp->obj_id == PLANE)
			plane_intersect(scene->cams->origin, ray, (t_plane *)test, dist);
		if (tmp->obj_id == CYL)
			cylinder_intersect(scene->cams->origin, ray, ((t_cylinder *)test), dist);
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

int	check_shadow(t_vector *origin, t_vector *direction, t_scene *scene)
{
	t_list		*tmp;
	t_list		*closer;
	float		dist[2];
	void		*test;
	float		closest;

	closer = NULL;
	closest = INFINITY;
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
			closest = dist[0];
			closer = tmp;
		}
		if (dist[1] >= 0.001f && dist[1] <= 1)
		{
			closest = dist[1];
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

static float compute_light(t_list *closer, float closer_dist, t_vector *ray, t_scene *scene)
{
	t_vector *mult;
	t_vector *point;
	t_vector *normal;
	t_vector *vec_l;
	t_vector *vec_r;
	// t_vector *view;
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
	vec_l = vec_substract(point, scene->light->point);
	intensity = 0;
	intensity += scene->ambient->lighting_ratio;
	if (check_shadow(point, vec_l, scene))
		return (intensity);
	n_dot = vec_dot_product(normal, vec_l);
	if (n_dot > 0)
		intensity += scene->light->brightness_ratio * n_dot / (vec_length(vec_l));
	vec_r = vec_substract(vec_mult(2 * vec_dot_product(normal, vec_l), normal), vec_l);
	// view = vec_mult(-1, ray);
	r_dot_v = vec_dot_product(vec_r, ray);
	if (r_dot_v > 0)
		intensity += scene->light->brightness_ratio * pow(r_dot_v / vec_length(vec_r), 500);
	// free(mult);
	// free(point);
	// if (closer->obj_id == 1)
	// 	free(normal);
	// free(vec_l);
	// free(vec_r);
	// free(view);
	return (intensity);
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
