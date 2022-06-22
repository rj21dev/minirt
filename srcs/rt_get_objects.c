/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:25:27 by coverand          #+#    #+#             */
/*   Updated: 2022/06/22 16:11:59 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_get_sphere(char **elem, t_scene **scene)
{
	t_sphere	*sphere;
	t_list		*obj;

	// obj = NULL;
	sphere = malloc(sizeof(sphere));
	if (!sphere)
		ft_errors_handler(strerror(errno));
	sphere->center = ft_get_coordiantes(elem[1]);
	sphere->radius = ft_atof(elem[2]) / 2;
	sphere->color_struct = ft_get_color_struct(elem[3]);
	sphere->color = ft_get_color(sphere->color_struct.r, \
	sphere->color_struct.g, sphere->color_struct.b);
	obj = ft_lstnew((void *)sphere);
	ft_lstadd_back(&(*scene)->elements, obj);
	ft_lstadd_back(&(*scene)->id, ft_lstnew((void *)SPHERE));
}

void	ft_get_cylinder(char **elem, t_scene **scene)
{
	t_cylinder	*cylinder;
	t_list		*obj;

	obj = NULL;
	cylinder = malloc(sizeof(cylinder));
	if (!cylinder)
		ft_errors_handler(strerror(errno));
	cylinder->point = ft_get_coordiantes(elem[1]);
	cylinder->or_vec = ft_get_coordiantes(elem[2]);
	cylinder->diameter = ft_atof(elem[3]);
	cylinder->height = ft_atof(elem[4]);
	cylinder->color_struct = ft_get_color_struct(elem[5]);
	cylinder->color = ft_get_color(cylinder->color_struct.r, \
	cylinder->color_struct.g, cylinder->color_struct.b);
	obj = ft_lstnew((void *)cylinder);
	ft_lstadd_back(&(*scene)->elements, obj);
	ft_lstadd_back(&(*scene)->id, ft_lstnew((void *)CYL));
}
