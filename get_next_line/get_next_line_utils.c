/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 14:19:53 by coverand          #+#    #+#             */
/*   Updated: 2021/12/03 15:04:37 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*Allocates and returns a new string, 
which is the result of the concatenation of ’s1’ and ’s2’*/
char	*ft_strjoin_modified(char const *s1, char const *s2, int len2)
{
	int		len1;
	char	*str;
	int		i;

	if (!s2)
		return (0);
	if (!s1)
		s1 = ft_strdup("");
	i = 0;
	len1 = ft_strlen(s1);
	str = malloc(sizeof(*str) * (len1 + len2) + 1);
	if (str == 0)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (i - len1 <= len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	free((void *)s1);
	return (str);
}
