/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:01:31 by coverand          #+#    #+#             */
/*   Updated: 2022/06/21 15:54:07 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

unsigned long	ft_get_color(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

t_color	ft_get_color_struct(char *str)
{
	t_color	color;
	char	**tmp;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	tmp = ft_split(str, ',');
	if (tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		color.r = ft_atoi(tmp[0]);
		color.g = ft_atoi(tmp[1]);
		color.b = ft_atoi(tmp[2]);
	}
	else
		ft_errors_handler(MAP_ERROR_WRONG_INP);
	return (color);
}

t_vector	*ft_get_coordiantes(char *str)
{
	char		**tmp;
	t_vector	*point;

	point = malloc(sizeof(t_vector));
	if (!point)
		ft_errors_handler(strerror(errno));
	tmp = ft_split(str, ',');
	if (tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		point->x = ft_atof(tmp[0]);
		point->y = ft_atof(tmp[1]);
		point->z = ft_atof(tmp[2]);
	}
	else
		ft_errors_handler(MAP_ERROR_WRONG_INP);
	return (point);
}

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

//A 0.2 255,255,255
//C -50.0,0,20 0,0,1 70
void	ft_get_elements(char **elem, t_scene **scene)
{
	if (!ft_strcmp(elem[0], "A") && elem[1] && elem[2] && !elem[3])
		ft_get_ambient_lightning(elem, scene);
	if (!ft_strcmp(elem[0], "C") && elem[1] && elem[2] && elem[3] && !elem[4])
	 	ft_get_camera(elem, scene);
	// printf("lr: %f\n", (*scene)->ambient->lighting_ratio);
	// printf("col: %lu\n", (*scene)->ambient->rgb);
	if ((*scene)->cams)
	{
		printf("fov: %f\n", (*scene)->cams->fov);
		printf("origin: %f, %f, %f\n", (*scene)->cams->origin->x, (*scene)->cams->origin->y, (*scene)->cams->origin->z);
	}
}

