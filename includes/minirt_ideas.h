/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_ideas.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:33:48 by coverand          #+#    #+#             */
/*   Updated: 2022/06/20 20:12:38 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <math.h>
/*incl minilibx lib*/

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
typedef struct point
{
	double	x;
	double	y;
	double	z;
}	t_point;

/* Struct for (R, G, B) colors.*/
typedef struct color
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
	double	lighting_ratio;
	t_color	color;
}	t_ambient;

/* Camera struct
* point - x,y,z coordinates of the view point;
* or_vec - 3d normalized orientation vector;
* fov -  Horizontal field of view in degrees in range [0,180].
*/
typedef struct s_camera
{
	t_point	point;
	t_point	or_vec;
	double	fov;
}	t_camera;

/* Light struct
* point - x,y,z coordinates of the light point;
* brightness_ratio - the light brightness ratio in range [0.0,1.0].
*/
typedef struct s_light
{
	t_point	point;
	double	brightness_ratio;
	t_color	color;
}	t_light;

/* Sphere struct
* point - x,y,z coordinates of the sphere center;
* diameter - the sphere diameter.
*/
typedef struct s_sphere
{
	t_point	point;
	double	diameter;
	t_color	color;
}	t_sphere;

/* Plane struct
* point - x,y,z coordinates;
* or_vec - 3d normalized orientation vector.
*/
typedef struct s_plane
{
	t_point	point;
	t_point	or_vec;
	t_color	color;
}	t_plane;

/* Cylinder struct
* or_vec - 3d normalized orientation vector;
* diameter - the cylinder diameter;
∗ height - the cylinder height.
*/
typedef struct s_cylinder
{
	t_point	point;
	t_point	or_vec;
	double	diameter;
	double	height;
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

typedef struct s_data
{
	t_ambient	ambient; // don't wanna allocate
	t_camera	camera;
	t_light		light;
	t_elements	*elements;
	double		width;
	double		height;
	void		*mlx_ptr;
	void		*win_ptr;
}	t_data;

#endif
