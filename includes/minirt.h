/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:42:04 by rjada             #+#    #+#             */
/*   Updated: 2022/06/21 22:59:17 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>

# define _INFINITY 999999999.f
# define BACKGROUND_COLOR 0x000000

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
	int			color;
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
	t_list		*objs;
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
float		vec_length(t_vector *vec);
void		vec_normalize(t_vector *vec);
float		vec_dot_product(t_vector *vec1, t_vector *vec2);

t_data		*init_data(int width, int height);

void		error_exit(int code);
int			color_mixer(int r, int g, int b);

t_camera	*new_cam(t_vector *origin, t_vector *direction, float fov);
t_sphere	*new_sphere(t_vector *center, float radius, int color);
t_scene		*new_scene(t_camera *cam, t_list *objs);

void		render_scene(t_data *data, t_scene *scene);
t_vplane	*get_view_plane(float width, float height, float fov);
void		sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere, float *dist1, float *dist2);

int			close_win(t_data *data);

#endif
