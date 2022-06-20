/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:42:04 by rjada             #+#    #+#             */
/*   Updated: 2022/06/20 17:27:00 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include "errors.h"

/*fonts color*/
# define FBLACK		"\033[0;30m"
# define FRED		"\033[0;31m"
# define FGREEN		"\033[0;32m"
# define FYELLOW	"\033[0;33m"
# define FBLUE		 "\033[0;34m"
# define FPURPLE	"\033[0;35m"
# define FCYAN		"\x1b[36m"

/*end color*/
# define NONE        "\033[0m"

/* Struct for points with (x, y, z) coordinates.*/
typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}		t_vector;

/* Struct for (R, G, B) colors.*/
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* Ambient lightning struct
* lighting_ratio - ambient lighting ratio in range [0.0,1.0]
*/
typedef struct s_ambient
{
	float	lighting_ratio;
	t_color	color;
}	t_ambient;

/* Camera struct
* origin - x,y,z coordinates of the view point;
* direction - 3d normalized orientation vector;
* fov -  Horizontal field of view in degrees in range [0,180].
*/
typedef struct s_camera
{
	t_vector	*origin;
	t_vector	*direction;
	float		fov;
}				t_camera;

/* Light struct
* point - x,y,z coordinates of the light point;
* brightness_ratio - the light brightness ratio in range [0.0,1.0].
*/
typedef struct s_light
{
	t_vector	point;
	float		brightness_ratio;
	t_color		color;
}	t_light;

/* Sphere struct
* center - x,y,z coordinates of the sphere center;
* radius - the sphere radius.
*/
typedef struct s_sphere
{
	t_vector	*center;
	float		radius;
	t_color		color; // added
}				t_sphere;

// CHECK VIDEO
typedef struct s_vplane
{
	float	width;
	float	height;
	float	x_pixel;
	float	y_pixel;
}				t_vplane;

/* Cylinder struct
* or_vec - 3d normalized orientation vector;
* diameter - the cylinder diameter;
∗ height - the cylinder height.
*/
typedef struct s_cylinder
{
	t_vector	point;
	t_vector	or_vec;
	float		diameter;
	float		height;
	t_color	color;
}	t_cylinder;

/*
list, where element is one of the stucts: t_sphere, t_plane, t_cylinder;
*/
typedef struct s_elements
{
	void			*element;
	struct elements	*next;
}	t_elements;

typedef struct s_scene
{
	t_camera	*cams;
	t_sphere	*spheres;
	float		width;
	float		height;
	t_ambient	ambient; // don't wanna allocate
	t_camera	camera;
	t_light		light;
	t_elements	*elements;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_scene;

t_vector	*new_vector(float x, float y, float z);
t_vector	*vec_substract(t_vector *vec1, t_vector *vec2);
float		vec_length(t_vector *vec);
void		vec_normalize(t_vector *vec);
float		vec_dot_product(t_vector *vec1, t_vector *vec2);

void		error_exit(int code);

t_camera	*new_cam(t_vector *origin, t_vector *direction, float fov);
t_sphere	*new_sphere(t_vector *center, float radius);
t_scene		*new_scene(t_camera *cam, t_sphere *sphere);

void		ray_traycing(void *mlx, void *window, t_scene *scene);
t_vplane	*get_view_plane(float width, float height, float fov);
int			sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere);

int	ft_errors_handler(char *msg);

#endif