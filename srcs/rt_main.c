/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:23 by rjada             #+#    #+#             */
/*   Updated: 2022/07/01 15:29:09 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	t_scene		*scene;

	if (argc != 2)
		ft_errors_handler(ARGS_COUNT_FAILURE);
	ft_check_extension(argv[1]);
	scene = ft_init();
	ft_read_from_file(argv[1], &scene);

	data = init_data();
	data->scene = scene;
/*	// DEBUG_PRINT Parser!!!
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
	}*/
	render_scene(data, scene);
	mlx_key_hook(data->win_ptr, key_hook, (void *)data);
	mlx_hook(data->win_ptr, 17, 0, close_win, data);
	mlx_loop(data->mlx_ptr);
	ft_clear(&scene);
	return (0);
}
