/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:42:04 by rjada             #+#    #+#             */
/*   Updated: 2022/06/20 16:42:19 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}		t_vector;

typedef struct	s_sphere
{
	t_vector	*center;
	float		radius;
}				t_sphere;

typedef struct	s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	float		fov;
}				t_camera;

typedef struct	s_scene
{
	t_camera	*cams;
	t_sphere	*spheres;
	float		width;
	float		height;
}				t_scene;

typedef struct	s_vplane
{
	float	width;
	float	height;
	float	x_pixel;
	float	y_pixel;
}				t_vplane;

t_vector	*new_vector(float x, float y, float z);
t_vector	*vec_substract(t_vector *vec1, t_vector *vec2);
float	vec_length(t_vector *vec);
void	vec_normalize(t_vector *vec);
float	vec_dot_product(t_vector *vec1, t_vector *vec2);

void	error_exit(int code);

t_camera	*new_cam(t_vector *origin, t_vector *direction, float fov);
t_sphere	*new_sphere(t_vector *center, float radius);
t_scene	*new_scene(t_camera *cam, t_sphere *sphere);

void	ray_traycing(void *mlx, void *window, t_scene *scene);
t_vplane	*get_view_plane(float width, float height, float fov);
int	sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere);

#endif
