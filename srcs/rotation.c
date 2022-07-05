/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:27:59 by coverand          #+#    #+#             */
/*   Updated: 2022/07/05 14:50:31 by coverand         ###   ########.fr       */
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

void	ft_rotate_objects_help(t_v3 *point, int key, t_list *lst)
{
	typedef t_cylinder t_cyl;
	if (lst)
	{
		if (((t_object *)lst->content)->type != CYL && \
		((t_object *)lst->content)->type != PLANE)
			return ;
		if (((t_object *)lst->content)->type == CYL)
			point = &((t_cyl *)(((t_object *)lst->content)->ptr))->or_vec;
		if (((t_object *)lst->content)->type == PLANE)
			point = &((t_plane *)(((t_object *)lst->content)->ptr))->or_vec;
	}
	if (key == X_ROTATE_KEY)
		ft_x_rotation(point, X_ROTATION_ANGLE * M_PI / 180);
	if (key == Y_ROTATE_KEY)
		ft_y_rotation(point, Y_ROTATION_ANGLE * M_PI / 180);
	if (key == Z_ROTATE_KEY)
		ft_z_rotation(point, Z_ROTATION_ANGLE * M_PI / 180);
}

void	ft_rotate_objects(t_data *data, int key)
{
	t_v3	*point;
	t_list	*lst;

	typedef t_cylinder t_cyl;
	point = NULL;
	if (data->scene->obj && (data->scene->obj->type == PLANE || \
	data->scene->obj->type == CYL))
	{
		if (data->scene->obj->type == CYL)
			point = &((t_cyl *)(data->scene->obj->ptr))->or_vec;
		if (data->scene->obj->type == PLANE)
			point = &((t_plane *)(data->scene->obj->ptr))->or_vec;
		ft_rotate_objects_help(point, key, NULL);
		return ;
	}
	lst = data->scene->elements;
	while (lst)
	{
		ft_rotate_objects_help(point, key, lst);
		lst = lst->next;
	}
}
