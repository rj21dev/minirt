/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_get_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:25:27 by coverand          #+#    #+#             */
/*   Updated: 2022/06/28 16:04:26 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_get_sphere(char **elem, t_scene **scene)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		ft_errors_handler(strerror(errno));
	sphere->center = ft_get_coordiantes(elem[1]);
	sphere->radius = ft_atof(elem[2]) / 2;
	sphere->color_struct = ft_get_color_struct(elem[3]);
	sphere->color = ft_get_color(sphere->color_struct.r, \
	sphere->color_struct.g, sphere->color_struct.b);
	ft_lstadd_back(&(*scene)->elements, ft_lstnew((void *)sphere, SPHERE));
}

void	ft_get_cylinder(char **elem, t_scene **scene)
{
	t_cylinder	*cylinder;
	t_list		*obj;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		ft_errors_handler(strerror(errno));
	cylinder->point = ft_get_coordiantes(elem[1]);
	cylinder->or_vec = ft_get_coordiantes(elem[2]);
	if (ft_orientation_vector_check(cylinder->or_vec))
		ft_errors_handler(ORIENTATION_VECTOR_ERR);
	cylinder->diameter = ft_atof(elem[3]);
	cylinder->height = ft_atof(elem[4]);
	cylinder->color_struct = ft_get_color_struct(elem[5]);
	cylinder->color = ft_get_color(cylinder->color_struct.r, \
	cylinder->color_struct.g, cylinder->color_struct.b);
	obj = ft_lstnew((void *)cylinder, CYL);
	ft_lstadd_back(&((*scene)->elements), obj);
}

void	ft_get_plane(char **elem, t_scene **scene)
{
	t_plane	*plane;
	t_list	*obj;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		ft_errors_handler(strerror(errno));
	plane->point = ft_get_coordiantes(elem[1]);
	plane->or_vec = ft_get_coordiantes(elem[2]);
	if (ft_orientation_vector_check(plane->or_vec))
		ft_errors_handler(ORIENTATION_VECTOR_ERR);
	plane->color_struct = ft_get_color_struct(elem[3]);
	plane->color = ft_get_color(plane->color_struct.r, \
	plane->color_struct.g, plane->color_struct.b);
	obj = ft_lstnew((void *)plane, PLANE);
	ft_lstadd_back(&((*scene)->elements), obj);
}
