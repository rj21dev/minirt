/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:23 by rjada             #+#    #+#             */
/*   Updated: 2022/06/21 10:31:05 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int	close_win(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	free(data);
	exit(EXIT_SUCCESS);
}

static t_data	*init_data(int width, int height)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "Ray Tracer");
	data->img = mlx_new_image(data->mlx_ptr, width, height);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->len, &data->endian);
	data->width = width;
	data->height = height;
	return (data);
}

int	main(void)
{
	t_data	*data;

	t_vector	*sphere_center = new_vector(0, 0, 15);
	t_sphere	*sphere = new_sphere(sphere_center, 5);
	t_vector	*cam_origin = new_vector(0, 0, 0);
	t_vector	*cam_direction = new_vector(0, 0, 1);
	t_camera	*cam = new_cam(cam_origin, cam_direction, 70);
	t_scene		*scene = new_scene(cam, sphere);
	scene->width = 800;
	scene->height = 600;
	data = init_data(scene->width, scene->height);
	render_scene(data, scene);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_loop(data->mlx_ptr);
	//free_scene(scene);
	free(sphere_center);
	free(sphere);
	free(cam_origin);
	free(cam_direction);
	free(cam);
	free(scene);
	// free(data); //free in close_win
	return (0);
}
