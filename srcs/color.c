/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:41:32 by rjada             #+#    #+#             */
/*   Updated: 2022/07/04 00:54:53 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_color	int_to_color(int color)
{
	t_int_color	a;
	t_color		rtn;

	a.integer = color;
	rtn.red = a.comps[2];
	rtn.green = a.comps[1];
	rtn.blue = a.comps[0];
	return (rtn);
}

int	color_to_int(t_color color)
{
	t_int_color	a;

	a.comps[2] = color.red;
	a.comps[1] = color.green;
	a.comps[0] = color.blue;
	return (a.integer);
}

t_color2	int_color(int color)
{
	t_color		tmp;
	t_color2	rtn;

	tmp = int_to_color(color);
	rtn.red = (float)tmp.red / 256;
	rtn.green = (float)tmp.green / 256;
	rtn.blue = (float)tmp.blue / 256;
	return (rtn);
}
