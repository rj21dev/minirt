/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_matrix_rot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 22:46:03 by rjada             #+#    #+#             */
/*   Updated: 2022/07/01 22:58:13 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector	mult_by_matrix(t_vector p, t_matrix m)
{
	t_vector	result;

	result.x = p.x * m.r[0][0] + p.y * m.r[1][0] + p.z * m.r[2][0] + m.r[3][0];
	result.y = p.x * m.r[0][1] + p.y * m.r[1][1] + p.z * m.r[2][1] + m.r[3][1];
	result.z = p.x * m.r[0][2] + p.y * m.r[1][2] + p.z * m.r[2][2] + m.r[3][2];
	return (result);
}

t_matrix	look_at(t_vector origin, t_vector direction)
{
	t_matrix	m;
	t_vector	init;
	t_vector	right;
	t_vector	up;

	init = new_vector(0, 1, 0);
	vec_normalize(&init);
	right = vec_cross_prod(init, direction);
	vec_normalize(&right);
	up = vec_cross_prod(direction, right);
	vec_normalize(&up);
	m.r[0][0] = right.x;
	m.r[0][1] = right.y;
	m.r[0][2] = right.z;
	m.r[1][0] = up.x;
	m.r[1][1] = up.y;
	m.r[1][2] = up.z;
	m.r[2][0] = direction.x;
	m.r[2][1] = direction.y;
	m.r[2][2] = direction.z;
	m.r[3][0] = origin.x;
	m.r[3][1] = origin.y;
	m.r[3][2] = origin.z;
	return (m);
}
