/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:27:24 by coverand          #+#    #+#             */
/*   Updated: 2022/07/05 19:18:46 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_rotate_camera(t_data *data, int key)
{
	t_v3	*point;
	double	rot;	

	printf("Rotating camera...\n");
	rot = data->scene->rotation;
	point = &data->scene->cams->direction;
	if (key == KEY_UP)
		ft_x_rotation(point, rot * MOVE_CAMERA_DOWN_UP * M_PI / 180);
	if (key == KEY_DOWN)
		ft_x_rotation(point, rot * -MOVE_CAMERA_DOWN_UP * M_PI / 180);
	if (key == KEY_RIGHT)
		ft_y_rotation(point, rot * MOVE_CAMERA_R_L * M_PI / 180);
	if (key == KEY_LEFT)
		ft_y_rotation(point, rot * -MOVE_CAMERA_R_L * M_PI / 180);
}

void	ft_move_camera(t_data *data, int key)
{
	printf("Moving camera...\n");
	if (key == KEY_W)
		data->scene->shift.y += 0.5;
	if (key == KEY_S)
		data->scene->shift.y -= 0.5;
	if (key == KEY_A)
		data->scene->shift.x -= 0.5;
	if (key == KEY_D)
		data->scene->shift.x += 0.5;
	if (key == KEY_R)
		data->scene->shift.z += 0.5;
	if (key == KEY_F)
		data->scene->shift.z -= 0.5;
}

void	ft_change_light_ratio(t_data *data, int key)
{
	printf("Changing light intensity...\n");
	if (key == KEY_SPACE)
		data->scene->light->intensity += 0.05;
	if (key == KEY_BACK)
		data->scene->light->intensity -= 0.05;
	if (data->scene->light->intensity > 1)
		data->scene->light->intensity = 1;
	if (data->scene->light->intensity < 0)
		data->scene->light->intensity = 0;
}
