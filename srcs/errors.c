/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:24:06 by coverand          #+#    #+#             */
/*   Updated: 2022/07/04 00:55:09 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_errors_handler(char *msg)
{
	ft_putstr_fd(FRED, STDERR);
	ft_putendl_fd(msg, STDERR);
	ft_putstr_fd(NONE, STDERR);
	exit(EXIT_FAILURE);
}
