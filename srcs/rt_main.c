/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:23 by rjada             #+#    #+#             */
/*   Updated: 2022/06/20 22:21:19 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_data	*init_data(int width, int height)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "Ray Tracer");
	data->img = mlx_new_image(data->mlx_ptr, width, height);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->len, &data->endian);
	return (data);
}

int	main(void)
{
	t_data	*data;

	t_vector	*sphere_center = new_vector(0, -1, 3);
	t_sphere	*sphere = new_sphere(sphere_center, 1);
	t_vector	*cam_origin = new_vector(0, 0, 0);
	t_vector	*cam_direction = new_vector(0, 0, 1);
	t_camera	*cam = new_cam(cam_origin, cam_direction, 70);
	t_scene		*scene = new_scene(cam, sphere);
	scene->width = 800;
	scene->height = 600;
	data = init_data(scene->width, scene->height);
	ray_traycing(data, scene);
	mlx_loop(data->mlx_ptr);
	//free_scene(scene);
	free(sphere_center);
	free(sphere);
	free(cam_origin);
	free(cam_direction);
	free(cam);
	free(scene);
	free(data);
	return (0);
}
