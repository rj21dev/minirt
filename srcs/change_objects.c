/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:29:27 by coverand          #+#    #+#             */
/*   Updated: 2022/07/05 17:38:16 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static t_v3	*add_vectors_modified(t_v3 *v1, t_v3 v2)
{
	v1->x += v2.x;
	v1->y += v2.z;
	v1->z += v2.z;
	return (v1);
}

void	ft_shift_object(t_data *data, int key, int x, int y)
{
	t_v3	*point;
	t_v3	direction;

	direction = get_direction(x, y, data->scene);
	if (data->scene->obj->type == SPHERE)
		point = & ((t_sphere *)(data->scene->obj->ptr))->center;
	if (data->scene->obj->type == CYL)
		point = & ((t_cylinder *)(data->scene->obj->ptr))->point;
	if (data->scene->obj->type == PLANE)
		point = & ((t_plane *)(data->scene->obj->ptr))->point;
	if (key == KEY_PLUS)
		point = add_vectors_modified(point, vec_mult(direction, 2));
	if (key == KEY_MINUS)
		point = add_vectors_modified(point, vec_mult(direction, -2));
	if (key == KEY_UP)
		point->y += 0.5;
	if (key == KEY_DOWN)
		point->y -= 0.5;
	if (key == KEY_RIGHT)
		point->x += 0.5;
	if (key == KEY_LEFT)
		point->x -= 0.5;
}

void	ft_change_objects_size(t_data *data, double change_size)
{
	if (data->scene->obj->type == SPHERE)
		((t_sphere *)(data->scene->obj->ptr))->radius += change_size;
	if (data->scene->obj->type == CYL)
	{
		if (data->scene->cyl_height % 2 == 0)
			((t_cylinder *)(data->scene->obj->ptr))->radius += change_size;
		else
			((t_cylinder *)(data->scene->obj->ptr))->height += change_size;
	}	
}