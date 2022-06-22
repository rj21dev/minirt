/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:01:31 by coverand          #+#    #+#             */
/*   Updated: 2022/06/22 15:23:16 by coverand         ###   ########.fr       */
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
//cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
void	ft_get_elements(char **elem, t_scene **scene)
{
	if (!ft_strcmp(elem[0], "A") && elem[1] && elem[2] && !elem[3])
		ft_get_ambient_lightning(elem, scene);
	if (!ft_strcmp(elem[0], "C") && elem[1] && elem[2] && elem[3] && !elem[4])
		ft_get_camera(elem, scene);
	if (!ft_strcmp(elem[0], "L") && elem[1] && elem[2] && elem[3] && !elem[4])
		ft_get_light(elem, scene);
	// if (!ft_strcmp(elem[0], "sp") && elem[1] && elem[2] && elem[3] && !elem[4])
	// 	ft_get_sphere(elem, scene);
	// if (!ft_strcmp(elem[0], "cy") && elem[1] && elem[2] && elem[3] && elem[4] \
	// && elem[5] && !elem[6])
	// 	ft_get_cylinder(elem, scene);
	// int i = 0;
	// while (*elem)
	// {
	// 	i++;
	// 	elem++;
	// }
	// printf("num of elem: %i\n", i);
	// else
	// 	ft_errors_handler(MAP_ERROR_UNKNOWN_ID);
}

