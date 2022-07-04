/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:29:17 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 23:33:46 by coverand         ###   ########.fr       */
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

void	ft_move_camera(t_data *data, int key)
{
	if (key == KEY_W)
		data->scene->shift.y += 0.5;
	if (key == KEY_S)
		data->scene->shift.y -= 0.5;
	if (key == KEY_A)
		data->scene->shift.x -= 0.5;
	if (key == KEY_D)
		data->scene->shift.x += 0.5;
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
		ft_rotate_camera(data, key);
	if (key == KEY_A || key == KEY_D || key == KEY_W || key == KEY_S)
		ft_move_camera(data, key);
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
	&data->len, &data->endian);
	render_scene(data);
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

int	mouse_hook(int keycode, int __unused x, int __unused y, t_data __unused *data)
{
	t_object	*closest;
	double		d_min;
	double		change_size;

	change_size = 0;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (keycode == MOUSE_LEFT)
		data->scene->obj = intersect_all_return(data->scene->elements, \
		ray_to_pixel(x,  y, data->scene), &closest, &d_min);
	if (keycode == MOUSE_UP)
		change_size += 0.5;
	if (keycode == MOUSE_DOWN)
		change_size -= 0.5;
	if (data->scene->obj->type == SPHERE)
		((t_sphere *)(data->scene->obj->ptr))->radius += change_size;
	if (data->scene->obj->type == CYL)
		((t_cylinder *)(data->scene->obj->ptr))->radius += change_size;
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, \
	&data->len, &data->endian);
	render_scene(data);
	return (0);
}
