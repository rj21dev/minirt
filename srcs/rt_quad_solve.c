/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_quad_solve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:11:50 by rjada             #+#    #+#             */
/*   Updated: 2022/07/03 17:17:29 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	swap_doubles(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_abc	new_abc(double a, double b, double c)
{
	t_abc	result;

	result.a = a;
	result.b = b;
	result.c = c;
	return (result);
}

int	solve_quadratic(t_abc abc, double *x0, double *x1)
{
	double	discr;
	double	q;

	discr = pow(abc.b, 2) - 4 * abc.a * abc.c;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		*x0 = -0.5 * abc.b / abc.a;
		*x1 = *x0;
	}
	else
	{
		if (abc.b > 0)
			q = -1 * (abc.b + sqrt(discr)) / 2;
		else
			q = -1 * (abc.b - sqrt(discr)) / 2;
		*x0 = q / abc.a;
		*x1 = abc.c / q;
	}
	if (*x0 > *x1)
		swap_doubles(x0, x1);
	return (1);
}
