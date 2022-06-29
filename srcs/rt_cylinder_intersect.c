/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder_intersect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:34:41 by coverand          #+#    #+#             */
/*   Updated: 2022/06/29 17:40:16 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	ft_find_discr(float a, float b, float c)
{
	return (powf(b, 2) - 4 * c * a);
}

void	ft_check_height_cyl(t_vector *d, t_vector *x, \
t_cylinder *cyl, float *dist)
{
	float	z;

	z = vec_dot_product(d, cyl->or_vec) * (*dist) + \
	vec_dot_product(x, cyl->or_vec);
	if (z < 0 || z > cyl->height)
		dist[0] = _INFINITY;
}

void	ft_free_cylinder_help(t_vector *oc, t_abc *tmp, t_root *root)
{
	if (oc)
		free(oc);
	if (tmp)
		free(tmp);
	if (root)
		free(root);
}

t_abc	*ft_find_cylinder_coeffs(t_vector *ray, t_vector *oc, t_cylinder *cyl)
{
	t_abc	*tmp;

	tmp = malloc(sizeof(t_abc));
	if (!tmp)
		ft_errors_handler(strerror(errno));
	tmp->a = vec_dot_product(ray, ray) - \
	powf(vec_dot_product(ray, cyl->or_vec), 2);
	tmp->b = 2 * (vec_dot_product(ray, oc) - \
	(vec_dot_product(ray, cyl->or_vec) * vec_dot_product(oc, cyl->or_vec)));
	tmp->c = vec_dot_product(oc, oc) - \
	powf(vec_dot_product(oc, cyl->or_vec), 2) - powf(cyl->diameter / 2, 2);
	return (tmp);
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
void	cylinder_intersect(t_camera *cam, t_vector *ray, \
t_cylinder *cyl, float *dist)
{
	t_vector	*oc;
	t_abc		*tmp;
	float		discr;
	t_root		*root;

	root = malloc(sizeof(t_root));
	if (!root)
		ft_errors_handler(strerror(errno));
	oc = vec_substract(cam->origin, cyl->point);
	tmp = ft_find_cylinder_coeffs(ray, oc, cyl);
	discr = ft_find_discr(tmp->a, tmp->b, tmp->c);
	if (discr < 0)
	{
		ft_free_cylinder_help(oc, tmp, root);
		*dist = _INFINITY;
		return ;
	}
	root->root_1 = (-tmp->b - sqrt(discr)) / (2 * tmp->a);
	root->root_2 = (-tmp->b + sqrt(discr)) / (2 * tmp->a);
	*dist = min_f(root->root_1, root->root_2);
	ft_check_height_cyl(ray, oc, cyl, dist);
	ft_free_cylinder_help(oc, tmp, root);
}

