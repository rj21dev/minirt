/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:23:21 by rjada             #+#    #+#             */
/*   Updated: 2022/07/04 19:08:13 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*addr;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		addr = data->addr + (y * data->len + x * (data->bpp / 8));
		*(unsigned int *)addr = color;
	}
}

static int	intersect(t_ray ray, t_object *object, double *dist)
{
	if (object->type == SPHERE)
		return (sphere_intersect(ray, *(t_sphere *)object->ptr, dist));
	else if (object->type == PLANE)
		return (plane_intersect(ray, *(t_plane *)object->ptr, dist));
	else if (object->type == CYL)
		return (cylinder_intersect(ray, *(t_cylinder *)object->ptr, dist));
	return (0);
}

int	intersect_all(t_list *objects, t_ray ray, t_object **closest, double *d_min)
{
	t_list		*tmp;
	t_object	*current;
	double		dist;

	*closest = NULL;
	tmp = objects;
	*d_min = INFINITY;
	while (tmp)
	{
		current = tmp->content;
		if (intersect(ray, current, &dist))
		{
			if (dist < *d_min)
			{
				*closest = current;
				*d_min = dist;
			}
		}
		tmp = tmp->next;
	}
	if (*closest != NULL)
		return (1);
	else
		return (0);
}

static int	ray_trace(t_scene *scene, t_ray ray)
{
	double		d_min;
	t_object	*closest;
	t_color2	amb_color;
	t_color2	amb_apply;
	t_color2	light_apply;

	if (intersect_all(scene->elements, ray, &closest, &d_min))
	{
		amb_color = color2_coeff(scene->ambient->color, \
		scene->ambient->lighting_ratio);
		amb_apply = color2_mult(closest->color, amb_color);
		light_apply = calc_light(scene, ray, closest, d_min);
		return (to_int(color2_add(amb_apply, light_apply)));
	}
	else
		return (BACKGROUND_COLOR);
}

void	render_scene(t_data *data)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = ray_trace(data->scene, ray_to_pixel(x, y, data->scene));
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
}
