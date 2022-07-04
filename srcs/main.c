/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:23 by rjada             #+#    #+#             */
/*   Updated: 2022/07/04 16:10:07 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_scene	*scene;

	if (argc != 2)
		ft_errors_handler(ARGS_COUNT_FAILURE);
	ft_check_extension(argv[1]);
	scene = ft_init();
	ft_read_from_file(argv[1], &scene);
	data = init_data();
	data->scene = scene;
	render_scene(data);
	// if (data->scene->elements)
	// 	printf("type1: %i\n", ((t_object *)data->scene->elements->content)->type);
	mlx_key_hook(data->win_ptr, key_hook, (void *)data);
	mlx_hook(data->win_ptr, 17, 0, ft_close, (void *)data);
	mlx_loop(data->mlx_ptr);
	return (0);
}
