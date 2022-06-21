/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 22:58:25 by rjada             #+#    #+#             */
/*   Updated: 2022/06/21 22:58:56 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_data	*init_data(int width, int height)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "Ray Tracer");
	data->img = mlx_new_image(data->mlx_ptr, width, height);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->len, &data->endian);
	data->width = width;
	data->height = height;
	return (data);
}