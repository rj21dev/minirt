/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:42:04 by rjada             #+#    #+#             */
/*   Updated: 2022/07/04 21:00:47 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "errors.h"
# include "keys.h"

# define WIDTH 1024
# define HEIGHT 768

# define BACKGROUND_COLOR 0x000000
# define METALNESS 0.1

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

# define SPHERE	1
# define PLANE	2
# define CYL	3

# define X_ROTATION_ANGLE	5
# define Y_ROTATION_ANGLE	5
# define Z_ROTATION_ANGLE	90

# define MOVE_CAMERA_DOWN_UP	5
# define MOVE_CAMERA_R_L		5

typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
}				t_v3;

/* Struct for (R, G, B) colors.*/
typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

typedef struct s_color2
{
	float	red;
	float	green;
	float	blue;
}				t_color2;

typedef union u_int_color
{
	int				integer;
	unsigned char	comps[4];
}				t_int_color;

/* Ambient lightning struct
* lighting_ratio - ambient lighting ratio in range [0.0,1.0]
*/
typedef struct s_ambient
{
	float			lighting_ratio;
	t_color2		color;
}				t_ambient;

/* Light struct
* point - x,y,z coordinates of the light point;
* brightness_ratio - the light brightness ratio in range [0.0,1.0].
*/
typedef struct s_light
{
	t_v3		point;
	double		intensity;
	t_color2	color;
}				t_light;

/* Camera struct
* origin - x,y,z coordinates of the view point;
* direction - 3d normalized orientation vector;
* fov -  Horizontal field of view in degrees in range [0,180].
*/
typedef struct s_camera
{
	t_v3	origin;
	t_v3	direction;
	float	fov;
}				t_camera;

/* Sphere struct
* center - x,y,z coordinates of the sphere center;
* radius - the sphere radius.
*/
typedef struct s_sphere
{
	t_v3	center;
	double	radius;
}				t_sphere;

/* Cylinder struct
* or_vec - 3d normalized orientation vector;
* diameter - the cylinder diameter;
∗ height - the cylinder height.
*/
typedef struct s_cylinder
{
	t_v3	point;
	t_v3	or_vec;
	double	radius;
	double	height;
}				t_cylinder;

typedef struct s_plane
{
	t_v3	point;
	t_v3	or_vec;
}				t_plane;

typedef struct s_object
{
	int			type;
	void		*ptr;
	t_color2	color;
}				t_object;

typedef struct s_scene
{
	t_camera	*cams;
	int			width;
	int			height;
	t_ambient	*ambient;
	t_light		*light;
	t_list		*elements;
}				t_scene;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
	t_scene	*scene;
}				t_data;

typedef struct s_matrix
{
	double	d[4][3];
}				t_matrix;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
}				t_ray;

typedef struct s_inter
{
	t_v3		hit_p;
	t_v3		hit_n;
	t_object	*closest;
	t_ray		ray;
}				t_inter;

typedef struct s_abc
{
	float	a;
	float	b;
	float	c;
}				t_abc;

t_v3		new_v3(double x, double y, double z);
t_v3		vec_sub(t_v3 vec1, t_v3 vec2);
t_v3		vec_add(t_v3 vec1, t_v3 vec2);
t_v3		vec_mult(t_v3 vec, double scalar);
t_v3		cross_prod(t_v3 v1, t_v3 v2);
double		dot_prod(t_v3 v1, t_v3 v2);
double		vec_len(t_v3 vec);
void		vec_norm(t_v3 *vec);

int			color_to_int(t_color color);
int			to_int(t_color2 a);
t_color		int_to_color(int color);
t_color2	int_color(int color);
t_color2	color2_add(t_color2 a, t_color2 b);
t_color2	color2_mult(t_color2 a, t_color2 b);
t_color2	color2_coeff(t_color2 a, double coeff);

t_data		*init_data(void);

t_ray		create_ray(t_v3 origin, t_v3 direction);
t_ray		ray_to_pixel(int x, int y, t_scene *scene);

t_abc		new_abc(double a, double b, double c);
int			solve_quadratic(t_abc abc, double *x0, double *x1);

int			cylinder_intersect(t_ray ray, t_cylinder cylinder, double *dist);
int			sphere_intersect(t_ray ray, t_sphere sphere, double *dist);
int			plane_intersect(t_ray ray, t_plane plane, double *dist);
int			intersect_all(t_list *objects, t_ray ray, \
t_object **closest, double *d_min);

t_v3		get_normal(t_v3 point, t_object *object);
t_color2	calc_light(t_scene *scene, t_ray ray, \
t_object *closest, double d_min);
void		render_scene(t_data *data);

int			close_win(t_data *data);

int			ft_errors_handler(char *msg);
float		ft_atof(char *str);
int			ft_strcmp(char const *str1, char const *str2);
void		ft_check_number_input(char *str);
void		ft_check_number(char **str);

t_color2	ft_get_color_struct(char *str);
t_v3		ft_get_coordiantes(char *str);
int			ft_orientation_vector_check(t_v3 point);
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

/* File key_hook.c */
int			key_hook(int key, void *param);
int			ft_close(t_data *data);

/* File rt_rotation.c */
void		ft_rotate_objects(t_data *data, int key);
void		ft_x_rotation(t_v3 *point, float angle);
void		ft_y_rotation(t_v3 *point, float angle);
void		ft_z_rotation(t_v3 *point, float angle);

t_color2	ft_find_color(t_light *light, t_inter inter, double coeff);
t_color2	calc_specular(t_light *light, t_inter inter);

#endif
