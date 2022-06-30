/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:29:17 by coverand          #+#    #+#             */
/*   Updated: 2022/06/30 15:00:54 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_x_rotation(t_vector *point, float angle)
{
	float	tmp_y;
	// float	tmp_z;

	tmp_y = point->y;
	// tmp_z = point->z;
	point->y = point->y * cosf(angle) + point->z * sinf(angle);
	point->z = -tmp_y * sinf(angle) + point->z * cosf(angle);
}

void	ft_y_rotation(t_vector *point, float angle)
{
	point->x = point->x * cosf(angle) + point->z * sinf(angle);
	point->z = -point->x * sinf(angle) + point->z * cosf(angle);
}

int	key_hook(int key, void *param)
{
	t_data	*data;

	data = param;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	if (key == 14)
	{
		if (data->scene->elements)
		{
			if (data->scene->elements->obj_id == CYL)
			{
				ft_x_rotation(((t_cylinder *)(data->scene->elements->content))->or_vec, 5 * M_PI / 180);
				printf("vector_y: %f\n", ((t_cylinder *)(data->scene->elements->content))->or_vec->y);
				printf("vector_z: %f\n", ((t_cylinder *)(data->scene->elements->content))->or_vec->z);
			}
		}
	}
	mlx_destroy_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->len, &data->endian);
	render_scene(data, data->scene);
	return (0);
}
