/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:22:13 by coverand          #+#    #+#             */
/*   Updated: 2022/06/20 17:40:48 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_strcmp(char const *str1, char const *str2)
{
	int	i;

	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

void	ft_check_extension(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot)
		ft_errors_handler(WRONG_EXTENSION);
	if (strcmp(dot, ".rt"))
		ft_errors_handler(WRONG_EXTENSION);
	else
		printf("Nice");
}

int	main(int argc, char __unused **argv)
{
	if (argc != 2)
		ft_errors_handler(ARGS_COUNT_FAILURE);
	ft_check_extension(argv[1]);
	return (0);
}
