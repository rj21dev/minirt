/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:25:27 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 21:16:12 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_get_sphere(char **elem, t_scene **scene)
{
	t_sphere	*sphere;
	t_object	*obj;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		ft_errors_handler(strerror(errno));
	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_errors_handler(strerror(errno));
	sphere->center = ft_get_coordiantes(elem[1]);
	ft_check_number_input(elem[2]);
	sphere->radius = ft_atof(elem[2]) / 2;
	obj->ptr = (void *)sphere;
	obj->type = SPHERE;
	obj->color = ft_get_color_struct(elem[3]);
	ft_lstadd_back(&(*scene)->elements, ft_lstnew(obj));
}

void	ft_get_cylinder(char **elem, t_scene **scene)
{
	t_cylinder	*cylinder;
	t_object	*obj;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		ft_errors_handler(strerror(errno));
	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_errors_handler(strerror(errno));
	cylinder->point = ft_get_coordiantes(elem[1]);
	cylinder->or_vec = ft_get_coordiantes(elem[2]);
	if (ft_orientation_vector_check(cylinder->or_vec))
		ft_errors_handler(ORIENTATION_VECTOR_ERR);
	ft_check_number_input(elem[3]);
	ft_check_number_input(elem[4]);
	cylinder->radius = ft_atof(elem[3]) / 2;
	cylinder->height = ft_atof(elem[4]);
	obj->ptr = (void *)cylinder;
	obj->type = CYL;
	obj->color = ft_get_color_struct(elem[5]);
	ft_lstadd_back(&((*scene)->elements), ft_lstnew(obj));
}

void	ft_get_plane(char **elem, t_scene **scene)
{
	t_plane		*plane;
	t_object	*obj;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		ft_errors_handler(strerror(errno));
	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_errors_handler(strerror(errno));
	plane->point = ft_get_coordiantes(elem[1]);
	plane->or_vec = ft_get_coordiantes(elem[2]);
	if (ft_orientation_vector_check(plane->or_vec))
		ft_errors_handler(ORIENTATION_VECTOR_ERR);
	obj->ptr = (void *)plane;
	obj->type = PLANE;
	obj->color = ft_get_color_struct(elem[3]);
	ft_lstadd_back(&((*scene)->elements), ft_lstnew(obj));
}
