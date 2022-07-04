/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:29:17 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 17:32:42 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data)
	{
		ft_clear(&data->scene);
		free(data);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_rotate_camera(t_data *data, int key)
{
	t_v3	*point;

	point = &data->scene->cams->direction;
	if (key == KEY_UP)
		ft_x_rotation(point, MOVE_CAMERA_DOWN_UP * M_PI / 180);
	if (key == KEY_DOWN)
		ft_x_rotation(point, -MOVE_CAMERA_DOWN_UP * M_PI / 180);
	if (key == KEY_RIGHT)
		ft_y_rotation(point, MOVE_CAMERA_R_L * M_PI / 180);
	if (key == KEY_LEFT)
		ft_y_rotation(point, -MOVE_CAMERA_R_L * M_PI / 180);
}

int	key_hook(int key, void *param)
{
	t_data	*data;

	data = param;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (key == KEY_ESC)
		ft_close(data);
	if (key == X_ROTATE_KEY || key == Y_ROTATE_KEY || key == Z_ROTATE_KEY)
		ft_rotate_objects(data, key);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT)
	mlx_destroy_image(data->mlx_ptr, data->img);
		ft_rotate_camera(data, key);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
	&data->len, &data->endian);
	render_scene(data);
	return (0);
}
