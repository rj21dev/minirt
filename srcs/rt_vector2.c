/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:04:39 by rjada             #+#    #+#             */
/*   Updated: 2022/07/01 18:32:24 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	vec_add(t_vector vec1, t_vector vec2)
{
	t_vector	result;

	result = new_vector(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
	return (result);
}

t_vector	col_mult(float scalar, t_color col_struct)
{
	t_vector	result;

	result = new_vector(scalar * col_struct.r, scalar * col_struct.g, scalar * col_struct.b);
	return (result);
}

t_vector	vec_mult(float scalar, t_vector vec)
{
	t_vector	result;

	result = new_vector(scalar * vec.x, scalar * vec.y, scalar * vec.z);
	return (result);
}
