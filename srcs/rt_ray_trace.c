/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:46 by rjada             #+#    #+#             */
/*   Updated: 2022/06/21 22:54:11 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
/*
* Convert View Port Coords x = (-400, 400), y = (300, -300)
* to Canvas Coords x = (0, 800), y = (0, 600) and PutPixel
*/
	x = data->width / 2 + x;
	y = data->height / 2 - y;
	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

static int	ray_trace(t_vector *ray, t_scene *scene)
{
	float		dist1;
	float		dist2;
	float		closer_dist;
	t_sphere	*test;
	t_sphere	*closer;
	t_list		*tmp;
	
	closer_dist = _INFINITY;
	closer = NULL;
	tmp = scene->objs;
	while (tmp)
	{
		test = tmp->content;
		sphere_intersect(scene->cams, ray, test, &dist1, &dist2);
		if (dist1 > 1 && dist1 < closer_dist)
		{
			closer_dist = dist1;
			closer = test;
		}
		if (dist2 > 1 && dist2 < closer_dist)
		{
			closer_dist = dist2;
			closer = test;
		}
		tmp = tmp->next;
	}
	if (!closer)
		return (BACKGROUND_COLOR);
	return (closer->color);
}

void	render_scene(t_data *data, t_scene *scene)
{
	float		x_vp;
	float		y_vp;
	int			color;
	t_vector	*ray;
	t_vplane	*vp;

	vp = get_view_plane(scene->width, scene->height, scene->cams->fov);
	y_vp = scene->height / 2;
	while (y_vp >= scene->height / 2 * (-1))
	{
		x_vp = scene->width / 2 * (-1);
		while (x_vp <= scene->width / 2)
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
		error_exit(-1);
	aspect_ratio = width / height;
	vplane->width = 2 * (tan(fov / 2 * (M_PI / 180)));
	vplane->height = vplane->width / aspect_ratio;
	vplane->x_pixel = vplane->width / width;
	vplane->y_pixel = vplane->height / height;
	return (vplane);
}
