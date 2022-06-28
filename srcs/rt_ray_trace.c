/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:46 by rjada             #+#    #+#             */
/*   Updated: 2022/06/28 16:30:34 by coverand         ###   ########.fr       */
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
	void	*test;
	t_list	*closer;

	closer_dist = _INFINITY;
	closer = NULL;
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
		if (dist > 1 && dist < closer_dist)
		{
			closer_dist = dist;
			closer = tmp;
		}
		tmp = tmp->next;
	}
	if (!closer)
		return (BACKGROUND_COLOR);
	t_vector *mult = vec_mult(closer_dist, ray);
	t_vector *point = vec_add(scene->cams->origin, mult);
	t_vector *normal;
	if (closer->obj_id == 1)
		normal = vec_substract(((t_sphere *)(closer->content))->center, point);
	if (closer->obj_id == 2)
		normal = ((t_plane *)closer->content)->or_vec;
	if (closer->obj_id == 3)
		normal = ((t_cylinder *)closer->content)->or_vec;
	vec_normalize(normal);
	t_vector *vec_1 = vec_substract(scene->light->point, point);
	float n_dot = vec_dot_product(normal, vec_1);
	float intensity = 0;
	intensity += scene->ambient->lighting_ratio;
	if (n_dot > 0)
		intensity += scene->light->brightness_ratio * n_dot / vec_length(vec_1);
	t_vector *cols;
	if (closer->obj_id == 1)
		cols = col_mult(intensity, ((t_sphere *)closer->content)->color_struct);
	if (closer->obj_id == 2)
		cols = col_mult(intensity, ((t_plane *)closer->content)->color_struct);
	if (closer->obj_id == 3)
		cols = col_mult(intensity, ((t_cylinder *)closer->content)->color_struct);
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
