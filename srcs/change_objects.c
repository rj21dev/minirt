/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:29:27 by coverand          #+#    #+#             */
/*   Updated: 2022/07/07 19:47:19 by rjada            ###   ########.fr       */
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

static double	ft_find_rad(double a, double min_v, double max_v)
{
	return (fmin(fmax(a, min_v), max_v));
}

void	ft_shift_object(t_data *data, int key, int x, int y)
{
	t_v3	*point;
	t_v3	direction;

	printf("Moving/rotating object...\n");
	direction = get_direction(x, y, data->scene);
	if (data->scene->obj->type == SPHERE)
		point = & ((t_sphere *)(data->scene->obj->ptr))->center;
	if (data->scene->obj->type == CYL)
		point = & ((t_cylinder *)(data->scene->obj->ptr))->point;
	if (data->scene->obj->type == PLANE)
		point = & ((t_plane *)(data->scene->obj->ptr))->point;
	if (key == KEY_R)
		point = add_vectors_modified(point, vec_mult(direction, 1.1));
	if (key == KEY_F)
		point = add_vectors_modified(point, vec_mult(direction, -1.1));
	if (key == KEY_W)
		point->y += 0.5;
	if (key == KEY_S)
		point->y -= 0.5;
	if (key == KEY_D)
		point->x += 0.5;
	if (key == KEY_A)
		point->x -= 0.5;
}

void	ft_change_objects_size(t_data *data, double change_size)
{
	printf("Changing size of selected object...\n");
	if (data->scene->obj->type == SPHERE)
		((t_sphere *)(data->scene->obj->ptr))->radius = \
		ft_find_rad(((t_sphere *)(data->scene->obj->ptr))->radius + \
						change_size, MIN_RADIUS, MAX_RADIUS);
	if (data->scene->obj->type == CYL)
	{
		if (data->scene->cyl_height % 2 == 0)
		{
			((t_cylinder *)(data->scene->obj->ptr))->radius = \
			ft_find_rad(((t_cylinder *)(data->scene->obj->ptr))->radius + \
						change_size, MIN_RADIUS, MAX_RADIUS);
		}
		else
			((t_cylinder *)(data->scene->obj->ptr))->height = \
			ft_find_rad(((t_cylinder *)(data->scene->obj->ptr))->height + \
						change_size, MIN_HEIGHT, MAX_HEIGHT);
	}
}
