/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:23 by rjada             #+#    #+#             */
/*   Updated: 2022/06/24 16:11:38 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	// t_data		*data;
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
	printf("Here\n");
	if (argc != 2)
		ft_errors_handler(ARGS_COUNT_FAILURE);
	ft_check_extension(argv[1]);
	scene = ft_init();
	ft_read_from_file(argv[1], &scene);
	
	scene->width = 800;
	scene->height = 600;
	// data = init_data(scene->width, scene->height);
	if (scene->elements && scene->id)
		printf("size: %i, %i\n", ft_lstsize(scene->elements), ft_lstsize(scene->id));
	t_list		*elements;
	t_list		*id;
	elements = scene->elements;
	id = scene->id;
	while (elements && id)
	{
		if (!ft_strcmp((char *)(id->content), SPHERE))
		{
			printf("Sphere: %f,%f,%f %f %i,%i,%i\n", \
			((t_sphere *)(elements->content))->center->x, ((t_sphere *)(elements->content))->center->y, ((t_sphere *)(elements->content))->center->z, \
			((t_sphere *)(elements->content))->radius, \
			((t_sphere *)(elements->content))->color_struct.r, ((t_sphere *)(elements->content))->color_struct.g, ((t_sphere *)(elements->content))->color_struct.b);
		}
		if (!ft_strcmp((char *)(id->content), CYL))
		{
			printf("CYL: %f,%f,%f %f,%f,%f %f %f %i,%i,%i\n", \
			((t_cylinder *)(elements->content))->point->x, ((t_cylinder *)(elements->content))->point->y, ((t_cylinder *)(elements->content))->point->z, \
			((t_cylinder *)(elements->content))->or_vec->x, ((t_cylinder *)(elements->content))->or_vec->y, ((t_cylinder *)(elements->content))->or_vec->z, \
			((t_cylinder *)(elements->content))->diameter, ((t_cylinder *)(elements->content))->height, \
			((t_cylinder *)(elements->content))->color_struct.r, ((t_cylinder *)(elements->content))->color_struct.g, ((t_cylinder *)(elements->content))->color_struct.b);
		}
		if (!ft_strcmp((char *)(id->content), PLANE))
		{
			printf("Plane: %f,%f,%f %f,%f,%f %i,%i,%i\n", \
			((t_plane *)(elements->content))->point->x, ((t_plane *)(elements->content))->point->y, ((t_plane *)(elements->content))->point->z, \
			((t_plane *)(elements->content))->or_vec->x, ((t_plane *)(elements->content))->or_vec->y, ((t_plane *)(elements->content))->or_vec->z, \
			((t_plane *)(elements->content))->color_struct.r, ((t_plane *)(elements->content))->color_struct.g, ((t_plane *)(elements->content))->color_struct.b);
		}
		elements = elements->next;
		id = id->next;
	}
	// render_scene(data, scene);
	
	// mlx_hook(data->win_ptr, 17, 0, close_win, data);
	// mlx_loop(data->mlx_ptr);
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
