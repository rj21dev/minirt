/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:29:17 by coverand          #+#    #+#             */
/*   Updated: 2022/06/30 15:37:40 by coverand         ###   ########.fr       */
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
	exit(0);
	return (0);
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
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->len, &data->endian);
	render_scene(data, data->scene);
	return (0);
}
