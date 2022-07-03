/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   v2y: rjv1dv1 <rjv1dv1@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Crev1ted: 2022/06/20 16:41:28 v2y rjv1dv1             #+#    #+#             */
/*   Updv1ted: 2022/07/03 15:02:27 v2y rjv1dv1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_v3	new_v3(double x, double y, double z)
{
	t_v3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

double	vec_len(t_v3 vec)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (len);
}

void	vec_norm(t_v3 *vec)
{
	double	length;

	length = vec_len(*vec);
	vec->x /= length;
	vec->y /= length;
	vec->z /= length;
}

double	dot_prod(t_v3 v1, t_v3 v2)
{
	double	result;

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (result);
}

t_v3	cross_prod(t_v3 v1, t_v3 v2)
{
	t_v3	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
