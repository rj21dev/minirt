/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_required_elements.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:59:40 by coverand          #+#    #+#             */
/*   Updated: 2022/06/22 13:09:09 by coverand         ###   ########.fr       */
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
	(*scene)->ambient->lighting_ratio = ft_atof(elem[1]);
	(*scene)->ambient->color = ft_get_color_struct(elem[2]);
	(*scene)->ambient->rgb = ft_get_color((*scene)->ambient->color.r, \
	(*scene)->ambient->color.g, (*scene)->ambient->color.b);
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
	(*scene)->cams->fov = ft_atof(elem[3]);
}

void	ft_get_light(char **elem, t_scene **scene)
{
	if ((*scene)->light)
		ft_errors_handler(MAP_ERROR_DUPLICATE_L);
	(*scene)->light = malloc(sizeof(t_light));
	if (!(*scene)->light)
		ft_errors_handler(strerror(errno));
	(*scene)->light->point = ft_get_coordiantes(elem[1]);
	(*scene)->light->brightness_ratio = ft_atof(elem[2]);
	(*scene)->light->color = ft_get_color_struct(elem[3]);
	(*scene)->light->rgb = ft_get_color((*scene)->light->color.r, \
	(*scene)->light->color.g, (*scene)->light->color.b);
}
