/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:32 by rjada             #+#    #+#             */
/*   Updated: 2022/06/24 23:54:31 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static int clamp(int col)
{
	return (ft_min(255, ft_max(0, col)));
}

int	color_mixer(t_vector *cols)
{
	return (clamp((int)cols->x) << 16 | clamp((int)cols->y) << 8 | clamp((int)cols->z));
}
