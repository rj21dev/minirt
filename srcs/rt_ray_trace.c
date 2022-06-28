/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:46 by rjada             #+#    #+#             */
/*   Updated: 2022/06/28 12:30:14 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*addr;

	x = WIDTH / 2 + x;
	y = HEIGHT / 2 - y;
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		addr = data->addr + (y * data->len + x * (data->bpp / 8));
		*(unsigned int*)addr = color;
	}
}

static int	ray_trace(t_vector *ray, t_scene *scene)
{
	float		dist;
	float		closer_dist;
	t_list		*tmp;
	t_list		*tmp_elem;
	void	*test;
	void	*closer;
	int		obj_id;

	closer_dist = _INFINITY;
	closer = NULL;
	tmp = scene->elements;
	tmp_elem = (*scene).id;
	while (tmp && tmp_elem)
	{
		test = tmp->content;
		if (!strcmp((char *)tmp_elem->content, SPHERE))
		{
			sphere_intersect(scene->cams, ray, (t_sphere *)test, &dist);
			obj_id = 1;
		}
		if (!strcmp((char *)tmp_elem->content, PLANE))
		{
			plane_intersect(scene->cams, ray, (t_plane *)test, &dist);
			obj_id = 2;
		}
		if (!strcmp((char *)tmp_elem->content, CYL))
		{
			cylinder_intersect(scene->cams, ray, ((t_cylinder *)test), &dist);
			obj_id = 3;
		}
		if (dist > 1 && dist < closer_dist)
		{
			closer_dist = dist;
			closer = test;
		}
		tmp = tmp->next;
		tmp_elem = tmp_elem->next;
	}
	if (!closer)
		return (BACKGROUND_COLOR);
	t_vector *mult = vec_mult(closer_dist, ray);
	t_vector *point = vec_add(scene->cams->origin, mult);
	t_vector *normal;
	if (obj_id == 1)
		normal = vec_substract(((t_sphere *)closer)->center, point);
	if (obj_id == 2)
		normal = ((t_plane *)closer)->or_vec;
	if (obj_id == 3)
		normal = ((t_cylinder *)closer)->or_vec;
	vec_normalize(normal);
	t_vector *vec_1 = vec_substract(scene->light->point, point);
	float n_dot = vec_dot_product(normal, vec_1);
	float intensity = 0;
	intensity += scene->ambient->lighting_ratio;
	if (n_dot > 0)
		intensity += scene->light->brightness_ratio * n_dot / vec_length(vec_1);
	t_vector *cols;
	if (obj_id == 1)
		cols = col_mult(intensity, ((t_sphere *)closer)->color_struct);
	if (obj_id == 2)
		cols = col_mult(intensity, ((t_plane *)closer)->color_struct);
	if (obj_id == 3)
		cols = col_mult(intensity, ((t_cylinder *)closer)->color_struct);
	int color = color_mixer(cols);
	free(cols);
	free(point);
	// free(normal); //в цидиндре и плоскости малочится не тут!!!
	free(vec_1);
	free(mult);
	return (color);
}

void	render_scene(t_data *data, t_scene *scene)
{
	float		x_vp;
	float		y_vp;
	int			color;
	t_vector	*ray;
	t_vplane	*vp;

	vp = get_view_plane(scene->width, scene->height, scene->cams->fov);
	y_vp = HEIGHT / 2;
	while (y_vp >= HEIGHT / 2 * (-1))
	{
		x_vp = WIDTH / 2 * (-1);
		while (x_vp <= WIDTH / 2)
		{
			ray = new_vector(x_vp * vp->x_pixel, y_vp * vp->y_pixel, 1);
			vec_normalize(ray);
			color = ray_trace(ray, scene);
			my_mlx_pixel_put(data, x_vp, y_vp, color);
			free(ray);
			x_vp++;
		}
		y_vp--;
	}
	free(vp);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}

t_vplane	*get_view_plane(float width, float height, float fov)
{
	t_vplane	*vplane;
	float		aspect_ratio;

	vplane = malloc(sizeof(t_vplane));
	if (!vplane)
		ft_errors_handler(strerror(errno));
	aspect_ratio = width / height;
	vplane->width = 2 * (tan(fov / 2 * (M_PI / 180)));
	vplane->height = vplane->width / aspect_ratio;
	vplane->x_pixel = vplane->width / width;
	vplane->y_pixel = vplane->height / height;
	return (vplane);
}
