#include "../includes/minirt.h"

t_ray	create_ray(t_v3 origin, t_v3 direction)
{
	t_ray	rtn;

	rtn.origin = origin;
	rtn.direction = direction;
	return (rtn);
}

static t_v3	multiply_by_matrix(t_v3 p, t_matrix m)
{
	t_v3	rtn;

	rtn.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
	rtn.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
	rtn.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
	return (rtn);
}

static t_matrix	look_at(t_v3 origin, t_v3 cam_vector)
{
	t_matrix	m;
	t_v3		random;
	t_v3		right;
	t_v3		up;

	random = new_v3(0, 1, 0);
	vec_norm(&random);
	right = cross_prod(random, cam_vector);
	vec_norm(&right);
	up = cross_prod(cam_vector, right);
	vec_norm(&up);
	m.d[0][0] = right.x;
	m.d[0][1] = right.y;
	m.d[0][2] = right.z;
	m.d[1][0] = up.x;
	m.d[1][1] = up.y;
	m.d[1][2] = up.z;
	m.d[2][0] = cam_vector.x;
	m.d[2][1] = cam_vector.y;
	m.d[2][2] = cam_vector.z;
	m.d[3][0] = origin.x;
	m.d[3][1] = origin.y;
	m.d[3][2] = origin.z;
	return (m);
}

static t_v3	get_direction(int x, int y, t_scene *scene)
{
	double	fov_coeff;
	double	aspect_ratio;
	double	p_x;
	double	p_y;

	fov_coeff = tan((double)scene->cams->fov / 2 * M_PI / 180);
	aspect_ratio = (double)scene->width / (double)scene->height;
	p_x = (2 * (x + 0.5) / (double)scene->width - 1) * aspect_ratio * fov_coeff;
	p_y = (1 - 2 * (y + 0.5) / (double)scene->height) * fov_coeff;
	return (new_v3(p_x, p_y, 1));
}

t_ray	ray_to_pixel(int x, int y, t_scene *scene)
{
	t_v3		origin;
	t_v3		direction;
	t_matrix	c2w;

	c2w = look_at(scene->cams->origin, scene->cams->direction);
	origin = multiply_by_matrix(new_v3(0, 0, 0), c2w);
	direction = get_direction(x, y, scene);
	direction = multiply_by_matrix(direction, c2w);
	direction = vec_sub(direction, origin);
	vec_norm(&direction);
	return (create_ray(origin, direction));
}
