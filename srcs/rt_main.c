/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:23 by rjada             #+#    #+#             */
/*   Updated: 2022/06/23 17:01:57 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	// t_list		*objs = NULL;
	// t_vector	*sphere_center;
	// t_sphere	*sphere;
	// t_vector	*cam_origin;
	// t_vector	*cam_direction;
	// t_camera	*cam;
	t_scene		*scene;

	// sphere_center = new_vector(0, -5, 15);
	// sphere = new_sphere(sphere_center, 5, color_mixer(255, 255, 0));
	// ft_lstadd_back(&objs, ft_lstnew(sphere));

	// sphere_center = new_vector(0, 2, 20);
	// sphere = new_sphere(sphere_center, 7, color_mixer(255, 0, 0));
	// ft_lstadd_back(&objs, ft_lstnew(sphere));

	// sphere_center = new_vector(6, 0, 13);
	// sphere = new_sphere(sphere_center, 4, color_mixer(0, 255, 0));
	// ft_lstadd_back(&objs, ft_lstnew(sphere));

	// sphere_center = new_vector(0, 0, 22);
	// sphere = new_sphere(sphere_center, 10, color_mixer(0, 0, 255));
	// ft_lstadd_back(&objs, ft_lstnew(sphere));

	// cam_origin = new_vector(0, 0, 0);
	// cam_direction = new_vector(0, 0, 1);
	// cam = new_cam(cam_origin, cam_direction, 70);
	// scene = new_scene(cam, objs);
	
	if (argc != 2)
		ft_errors_handler(ARGS_COUNT_FAILURE);
	ft_check_extension(argv[1]);
	scene = ft_init();
	ft_read_from_file(argv[1], &scene);
	
	scene->width = 800;
	scene->height = 600;
	data = init_data(scene->width, scene->height);
	printf("lol\n");
	render_scene(data, scene);
	
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_loop(data->mlx_ptr);
	// //free_scene(scene);
	// // free(sphere_center);
	// // free(sphere);
	// // free(cam_origin);
	// // free(cam_direction);
	// // free(cam);
	// // free scene->objs !!!
	// // free(scene);
	// free(data); //free in close_win
	ft_clear(&scene);
	return (0);
}
