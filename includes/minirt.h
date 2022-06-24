/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:42:04 by rjada             #+#    #+#             */
/*   Updated: 2022/06/24 23:58:45 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include "errors.h"
# include <stdio.h>
# include <string.h>

# define WIDTH 1024
# define HEIGHT 768
# define _INFINITY 999999999.f
# define BACKGROUND_COLOR 0x000000

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

# define SPHERE	"sphere"
# define PLANE	"plane"
# define CYL	"cyl"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	float	width;
	float	height;
}	t_data;

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
	float			lighting_ratio;
	t_color			color;
	unsigned long	rgb;
}	t_ambient;

/* Light struct
* point - x,y,z coordinates of the light point;
* brightness_ratio - the light brightness ratio in range [0.0,1.0].
*/
typedef struct s_light
{
	t_vector	*point;
	float		brightness_ratio;
	t_color		color;
	int			rgb;
}	t_light;

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

/* Sphere struct
* center - x,y,z coordinates of the sphere center;
* radius - the sphere radius.
*/
typedef struct s_sphere
{
	t_vector	*center;
	float		radius;
	t_color		color_struct;
	int			color;
}				t_sphere;

/* Cylinder struct
* or_vec - 3d normalized orientation vector;
* diameter - the cylinder diameter;
∗ height - the cylinder height.
*/
typedef struct s_cylinder
{
	t_vector	*point;
	t_vector	*or_vec;
	float		diameter;
	float		height;
	t_color		color_struct;
	int			color;
}	t_cylinder;

typedef struct s_plane
{
	t_vector	*point;
	t_vector	*or_vec;
	t_color		color_struct;
	int			color;
}	t_plane;

typedef struct s_scene
{
	t_camera	*cams;
	float		width;
	float		height;
	t_ambient	*ambient;
	t_light		*light;
	t_list		*elements; //list, where element is one of the stucts: t_sphere, t_plane, t_cylinder;
	t_list		*id;

}				t_scene;

typedef struct s_vplane
{
	float	width;
	float	height;
	float	x_pixel;
	float	y_pixel;
}				t_vplane;

t_vector	*new_vector(float x, float y, float z);
t_vector	*vec_substract(t_vector *vec1, t_vector *vec2);
t_vector	*vec_add(t_vector *vec1, t_vector *vec2);
t_vector	*vec_mult(float scalar, t_vector *vec);
t_vector	*col_mult(float scalar, t_color col_struct);
float		vec_length(t_vector *vec);
float		vec_dot_product(t_vector *vec1, t_vector *vec2);
void		vec_normalize(t_vector *vec);

t_data		*init_data(void);

int			color_mixer(t_vector *cols);

void		render_scene(t_data *data, t_scene *scene);
t_vplane	*get_view_plane(float width, float height, float fov);
// void		sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere, float *dist1, float *dist2);
void		sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere, float *dist);

int			close_win(t_data *data);

//merge

int			ft_errors_handler(char *msg);

float		ft_atof(char *str);
int			ft_strcmp(char const *str1, char const *str2);

int			ft_get_color(int r, int g, int b);
t_color		ft_get_color_struct(char *str);
t_vector	*ft_get_coordiantes(char *str);
int			ft_orientation_vector_check(t_vector *point);
void		ft_get_elements(char **el, t_scene **scene);

void		ft_get_ambient_lightning(char **elem, t_scene **scene);
void		ft_get_camera(char **elem, t_scene **scene);
void		ft_get_light(char **elem, t_scene **scene);

void		ft_get_sphere(char **elem, t_scene **scene);
void		ft_get_cylinder(char **elem, t_scene **scene);
void		ft_get_plane(char **elem, t_scene **scene);

void		ft_clear(t_scene **scene);

t_scene		*ft_init(void);
void		ft_read_from_file(char *filename, t_scene **scene);
void		ft_check_extension(char *file);

#endif
