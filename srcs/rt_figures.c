/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_figures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:51 by rjada             #+#    #+#             */
/*   Updated: 2022/06/24 13:19:51 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_sphere	*new_sphere(t_vector *center, float radius, int r, int g, int b)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit(-1);
	sphere->center = center;
	sphere->radius = radius;
	sphere->cols = new_vector(r, g, b);
	return (sphere);
}
