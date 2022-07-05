/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:29:17 by coverand          #+#    #+#             */
/*   Updated: 2022/07/05 18:28:51 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_create_new_img(t_data *data)
{
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
	&data->len, &data->endian);
	render_scene(data);
}

int	ft_close(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data)
	{
		ft_clear(&data->scene);
		free(data);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int key, void *param)
{
	t_data	*data;

	data = param;
	if (key == KEY_ESC)
		ft_close(data);
	if (key == X_ROTATE_KEY || key == Y_ROTATE_KEY || key == Z_ROTATE_KEY)
		ft_rotate_objects(data, key);
	if ((key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || \
	key == KEY_RIGHT) && data->scene->shift_object % 2 == 0)
		ft_rotate_camera(data, key);
	if (key == KEY_A || key == KEY_D || key == KEY_W || key == KEY_S \
	|| key == KEY_R || key == KEY_F)
		ft_move_camera(data, key);
	if (key == KEY_H)
		data->scene->cyl_height += 1;
	if (key == KEY_M)
		data->scene->shift_object += 1;
	if (data->scene->obj && data->scene->shift_object % 2 != 0)
		ft_shift_object(data, key, data->scene->x, data->scene->y);
	if (key == KEY_SPACE || key == KEY_BACK)
		ft_change_light_ratio(data, key);
	ft_create_new_img(data);
	return (0);
}

t_object	*intersect_all_return(t_list *objects, t_ray ray, \
t_object **closest, double *d_min)
{
	t_list		*tmp;
	t_object	*current;
	double		dist;

	*closest = NULL;
	tmp = objects;
	*d_min = INFINITY;
	while (tmp)
	{
		current = tmp->content;
		if (intersect(ray, current, &dist))
		{
			if (dist < *d_min)
			{
				*closest = current;
				*d_min = dist;
			}
		}
		tmp = tmp->next;
	}
	return (*closest);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	t_object	*closest;
	double		d_min;
	double		change_size;

	change_size = 0;
	data->scene->x = x;
	data->scene->y = y;
	if (keycode == MOUSE_LEFT)
		data->scene->obj = intersect_all_return(data->scene->elements, \
		ray_to_pixel(x, y, data->scene), &closest, &d_min);
	if (keycode == MOUSE_UP)
		change_size += 0.5;
	if (keycode == MOUSE_DOWN)
		change_size -= 0.5;
	if (data->scene->obj)
		ft_change_objects_size(data, change_size);
	ft_create_new_img(data);
	return (0);
}
