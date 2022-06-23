/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:24:06 by coverand          #+#    #+#             */
/*   Updated: 2022/06/20 17:40:08 by coverand         ###   ########.fr       */
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
