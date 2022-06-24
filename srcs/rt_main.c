/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:23 by rjada             #+#    #+#             */
/*   Updated: 2022/06/24 19:40:31 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(void)
{
	t_data		*data;
	t_list		*objs = NULL;
	t_vector	*sphere_center;
	t_sphere	*sphere;
	t_vector	*cam_origin;
	t_vector	*cam_direction;
	t_camera	*cam;
	t_scene		*scene;

	
	// sphere_center = new_vector(3, 0, 10);
	// sphere = new_sphere(sphere_center, 3, 255, 0, 0);
	// ft_lstadd_back(&objs, ft_lstnew(sphere));

	sphere_center = new_vector(0, -1, 3);
	sphere = new_sphere(sphere_center, 1, 255, 0, 0);
	ft_lstadd_back(&objs, ft_lstnew(sphere));

	sphere_center = new_vector(2, 0, 4);
	sphere = new_sphere(sphere_center, 1, 0, 0, 255);
	ft_lstadd_back(&objs, ft_lstnew(sphere));

	sphere_center = new_vector(-2, 0, 4);
	sphere = new_sphere(sphere_center, 1, 0, 255, 0);
	ft_lstadd_back(&objs, ft_lstnew(sphere));

	sphere_center = new_vector(0, -5001, 0);
	sphere = new_sphere(sphere_center, 5000, 255, 255, 0);
	ft_lstadd_back(&objs, ft_lstnew(sphere));

	cam_origin = new_vector(0, 0, 0);
	cam_direction = new_vector(0, 0, 1);
	cam = new_cam(cam_origin, cam_direction, 70);
	scene = new_scene(cam, objs);
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
	// free scene->objs !!!
	free(scene);
	// free(data); //free in close_win
	return (0);
}
