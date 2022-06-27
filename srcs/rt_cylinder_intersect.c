/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder_intersect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:34:41 by coverand          #+#    #+#             */
/*   Updated: 2022/06/26 21:33:28 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	ft_find_discr(float a, float b, float c)
{
	return (powf(b, 2) - 4 * c * a);
}

// https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
/*
* ray - ray direction;
* 1) Find cam_cyl = ray origin - center point of shape
* 2) Find a, b, c coef:
	a   = D|D - (D|V)^2
	b/2 = D|X - (D|V)*(X|V)
	c   = X|X - (X|V)^2 - r*r
	
	D - the ray direction
	X - X equals O-C (ray origin - center point of shape)
	V - is a unit length vector that determines cylinder's axis
	r - is the cylinder's radius
*/
void	cylinder_intersect(t_camera *cam, t_vector *ray, t_cylinder *cyl, float *dist)
{
	t_vector	*cam_cyl;
	t_abc	*tmp = malloc(sizeof(t_abc));
	float	discr;
	cam_cyl = vec_substract(cam->origin, cyl->point);
	tmp->a = vec_dot_product(ray, ray) - powf(vec_dot_product(ray, cyl->or_vec), 2);
	tmp->b = 2 * (vec_dot_product(ray, cam_cyl) - (vec_dot_product(ray, cyl->or_vec) * vec_dot_product(cam_cyl, cyl->or_vec)));
	tmp->c = vec_dot_product(cyl->or_vec, cyl->or_vec) - powf(vec_dot_product(cam_cyl, cyl->or_vec), 2) - powf(cyl->diameter / 2, 2);
	discr = ft_find_discr(tmp->a, tmp->b, tmp->c);
	free(cam_cyl);
	if (discr < 0)
	{
		dist[0] = _INFINITY;
		dist[1] = _INFINITY;
		return ;
	}
	dist[0] = (-tmp->b - sqrt(discr)) / (2 * tmp->a);
	dist[1] = (-tmp->b + sqrt(discr)) / (2 * tmp->a);
}

