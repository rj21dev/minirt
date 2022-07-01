/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:23:21 by rjada             #+#    #+#             */
/*   Updated: 2022/07/01 22:10:01 by rjada            ###   ########.fr       */
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

static t_vplane	*get_view_plane(float width, float height, float fov)
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

void	render_scene(t_data *data, t_scene *scene)
{
	float		x_vp;
	float		y_vp;
	int			color;
	t_vector	ray;
	t_vplane	*vp;

	vp = get_view_plane(scene->width, scene->height, scene->cams->fov);
	y_vp = HEIGHT / 2;
	while (y_vp >= HEIGHT / 2 * (-1))
	{
		x_vp = WIDTH / 2 * (-1);
		while (x_vp <= WIDTH / 2)
		{
			ray = new_vector(x_vp * vp->x_pixel, y_vp * vp->y_pixel, 1);
			vec_normalize(&ray);
			color = ray_trace(ray, scene);
			my_mlx_pixel_put(data, x_vp, y_vp, color);
			x_vp++;
		}
		y_vp--;
	}
	free(vp);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}