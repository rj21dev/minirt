/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:23 by rjada             #+#    #+#             */
/*   Updated: 2022/06/20 16:41:26 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	t_vector	*sphere_center = new_vector(0, -1, -3);
	t_sphere	*sphere = new_sphere(sphere_center, 1);
	t_vector	*cam_origin = new_vector(0, 0, 0);
	t_vector	*cam_direction = new_vector(0, 0, 1);
	t_camera	*cam = new_cam(cam_origin, cam_direction, 70);
	t_scene		*scene = new_scene(cam, sphere);
	scene->width = 800;
	scene->height = 600;
	win = mlx_new_window(mlx, scene->width, scene->height, "Render");
	ray_traycing(mlx, win, scene);
	mlx_loop(mlx);
	//free_scene(scene);
	free(sphere_center);
	free(sphere);
	free(cam_origin);
	free(cam_direction);
	free(cam);
	free(scene);
	return (0);
}
