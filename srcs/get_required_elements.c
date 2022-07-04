/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_required_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:59:40 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 21:11:35 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_get_ambient_lightning(char **elem, t_scene **scene)
{
	if ((*scene)->ambient)
		ft_errors_handler(MAP_ERROR_DUPLICATE_A);
	(*scene)->ambient = malloc(sizeof(t_ambient));
	if (!(*scene)->ambient)
		ft_errors_handler(strerror(errno));
	ft_check_number_input(elem[1]);
	(*scene)->ambient->lighting_ratio = ft_atof(elem[1]);
	if ((*scene)->ambient->lighting_ratio > 1.0 || \
	(*scene)->ambient->lighting_ratio < 0.0)
		ft_errors_handler(AMBIENT_RATIO_RANGE_ER);
	(*scene)->ambient->color = ft_get_color_struct(elem[2]);
}

void	ft_get_camera(char **elem, t_scene **scene)
{
	if ((*scene)->cams)
		ft_errors_handler(MAP_ERROR_DUPLICATE_C);
	(*scene)->cams = malloc(sizeof(t_camera));
	if (!(*scene)->cams)
		ft_errors_handler(strerror(errno));
	(*scene)->cams->origin = ft_get_coordiantes(elem[1]);
	(*scene)->cams->direction = ft_get_coordiantes(elem[2]);
	if (ft_orientation_vector_check((*scene)->cams->direction))
		ft_errors_handler(ORIENTATION_VECTOR_ERR);
	ft_check_number_input(elem[3]);
	(*scene)->cams->fov = ft_atof(elem[3]);
	if ((*scene)->cams->fov < 0.0 || (*scene)->cams->fov > 180.0)
		ft_errors_handler(FOV_RANGE_ERR);
}

void	ft_get_light(char **elem, t_scene **scene)
{
	if ((*scene)->light)
		ft_errors_handler(MAP_ERROR_DUPLICATE_L);
	(*scene)->light = malloc(sizeof(t_light));
	if (!(*scene)->light)
		ft_errors_handler(strerror(errno));
	(*scene)->light->point = ft_get_coordiantes(elem[1]);
	ft_check_number_input(elem[2]);
	(*scene)->light->intensity = ft_atof(elem[2]);
	if ((*scene)->light->intensity > 1.0 || \
	(*scene)->light->intensity < 0.0)
		ft_errors_handler(BRIGHTNESS_RATIO_RANGE);
	(*scene)->light->color = ft_get_color_struct(elem[3]);
}
