/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:27:59 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 00:56:31 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_x_rotation(t_v3 *point, float angle)
{
	float	tmp_y;

	tmp_y = point->y;
	point->y = point->y * cosf(angle) + point->z * sinf(angle);
	point->z = -tmp_y * sinf(angle) + point->z * cosf(angle);
}

void	ft_y_rotation(t_v3 *point, float angle)
{
	float	tmp_x;

	tmp_x = point->x;
	point->x = point->x * cosf(angle) + point->z * sinf(angle);
	point->z = -tmp_x * sinf(angle) + point->z * cosf(angle);
}

void	ft_z_rotation(t_v3 *point, float angle)
{
	float	tmp_x;

	tmp_x = point->x;
	point->x = point->x * cosf(angle) - point->y * sinf(angle);
	point->y = tmp_x * sinf(angle) + point->y * cosf(angle);
}

void	ft_rotate_objects(t_data *data, int key)
{
	(void)data;
	(void)key;
	/*t_v3	point;

	if (data->scene->elements && (data->scene->elements->obj_id == CYL || \
	data->scene->elements->obj_id == PLANE))
	{
		if (data->scene->elements->obj_id == CYL)
			point = ((t_cylinder *)(data->scene->elements->content))->or_vec;
		if (data->scene->elements->obj_id == PLANE)
			point = ((t_plane *)(data->scene->elements->content))->or_vec;
		if (key == X_ROTATE_KEY)
			ft_x_rotation(&point, X_ROTATION_ANGLE * M_PI / 180);
		if (key == Y_ROTATE_KEY)
			ft_y_rotation(&point, Y_ROTATION_ANGLE * M_PI / 180);
		if (key == Z_ROTATE_KEY)
			ft_z_rotation(&point, Z_ROTATION_ANGLE * M_PI / 180);
	}*/
}
