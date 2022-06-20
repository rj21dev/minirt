/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:46 by rjada             #+#    #+#             */
/*   Updated: 2022/06/20 22:19:35 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	ray_traycing(t_data *data, t_scene *scene)
{
	int	mlx_x;
	int	mlx_y;
	float	x_angle;
	float	y_angle;
	float	x_ray;
	float	y_ray;
	int	color;
	t_vector	*ray;
	t_vplane	*vplane;

	vplane = get_view_plane(scene->width, scene->height, scene->cams->fov);
	y_angle = scene->height / 2;
	mlx_y = 0;
	while (y_angle >= scene->height / 2 * (-1))
	{
		y_ray = y_angle * vplane->y_pixel;
		x_angle = scene->width / 2 * (-1);
		mlx_x = 0;
		while (x_angle <= scene->width / 2)
		{
			x_ray = x_angle * vplane->x_pixel;
			ray = new_vector(x_ray, y_ray, 1);
			vec_normalize(ray);
			if (sphere_intersect(scene->cams, ray, scene->spheres))
				color = 0xffff00;
			else
				color = 0x000000;
			my_mlx_pixel_put(data, mlx_x, mlx_y, color);
			free(ray);
			x_angle++;
			mlx_x++;
		}
		y_angle--;
		mlx_y++; 
	}
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
