/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:01:31 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 00:55:13 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color2	ft_get_color_struct(char *str)
{
	t_color2	color;
	char	**tmp;

	color.red = 0;
	color.green = 0;
	color.blue = 0;
	tmp = ft_split(str, ',');
	if (tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		color.red = ft_atoi(tmp[0]) / 256.f;
		color.green = ft_atoi(tmp[1]) / 256.f;
		color.blue = ft_atoi(tmp[2]) / 256.f;
	}
	else
		ft_errors_handler(MAP_ERROR_WRONG_INP);
	ft_split_free(tmp);
	if (color.red > 255 || color.green > 255 || color.blue > 255 || \
	color.red < 0 || color.green < 0 || color.blue < 0)
		ft_errors_handler(RGB_COLORS_RANGE_ERR);
	return (color);
}

t_v3	ft_get_coordiantes(char *str)
{
	char		**tmp;
	t_v3	point;

	tmp = ft_split(str, ',');
	if (tmp[0] && tmp[1] && tmp[2] && !tmp[3])
	{
		point.x = ft_atof(tmp[0]);
		point.y = ft_atof(tmp[1]);
		point.z = ft_atof(tmp[2]);
	}
	else
		ft_errors_handler(MAP_ERROR_WRONG_INP);
	ft_split_free(tmp);
	return (point);
}

int	ft_orientation_vector_check(t_v3 point)
{
	if (point.x > 1.0 || point.y > 1.0 || point.z > 1.0 || \
	point.x < -1.0 || point.y < -1.0 || point.z < -1.0)
		return (1);
	return (0);
}

void	ft_get_elements(char **el, t_scene **scene)
{
	if (!ft_strcmp(el[0], "\n"))
		return ;
	else if (!ft_strcmp(el[0], "A") && el[1] && el[2] && !el[3])
		ft_get_ambient_lightning(el, scene);
	else if (!ft_strcmp(el[0], "C") && el[1] && el[2] && el[3] && !el[4])
		ft_get_camera(el, scene);
	else if (!ft_strcmp(el[0], "L") && el[1] && el[2] && el[3] && !el[4])
		ft_get_light(el, scene);
	else if (!ft_strcmp(el[0], "sp") && el[1] && el[2] && el[3] && !el[4])
		ft_get_sphere(el, scene);
	else if (!ft_strcmp(el[0], "pl") && el[1] && el[2] && el[3] && !el[4])
		ft_get_plane(el, scene);
	else if (!ft_strcmp(el[0], "cy") && el[1] && el[2] && el[3] && el[4] \
	&& el[5] && !el[6])
		ft_get_cylinder(el, scene);
	else
		ft_errors_handler(MAP_ERROR_UNKNOWN_ID);
}
