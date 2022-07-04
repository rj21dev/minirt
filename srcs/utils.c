/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:22:25 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 19:22:51 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color2	ft_find_color(t_light *light, t_inter inter, double coeff)
{
	t_color2	light_color;
	t_color2	object_color;
	t_color2	total;

	light_color = color2_coeff(light->color, light->intensity);
	object_color = inter.closest->color;
	total = color2_coeff(color2_mult(light_color, object_color), coeff);
	if (coeff)
		total = color2_add(total, calc_specular(light, inter));
	return (total);
}
