/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:03:59 by coverand          #+#    #+#             */
/*   Updated: 2022/06/23 19:25:02 by coverand         ###   ########.fr       */
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

static float	ft_get_decimal(char *str)
{
	float	decimal;
	size_t	i;
	size_t	j;

	decimal = 0;
	i = 0;
	j = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		decimal = decimal * 10 + str[i] - '0';
		++i;
		j++;
	}
	return (decimal / pow(10, j));
}

float	ft_atof(char *str)
{
	size_t	i;
	float	sign;
	float	res;
	float	decimal;

	sign = 1;
	res = 0;
	decimal = 0;
	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		++i;
	}
	if (str[i] && str[i++] == '.')
		decimal = ft_get_decimal(&str[i]);
	return (sign * (res + decimal));
}

// int main(void)
// {
// 	char *str = "-0.2";
// 	float n = ft_atof(str);
// 	printf("str: %f\n", n);
// 	printf("atof: %f\n", strtod(str, &str));
// }
