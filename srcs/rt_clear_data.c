/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_clear_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:09 by coverand          #+#    #+#             */
/*   Updated: 2022/06/22 16:34:32 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_clear_split(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
	str = NULL;
}

void	ft_clear(t_scene **scene)
{
	t_list	*tmp;

	if ((*scene)->cams)
	{
		if ((*scene)->cams->direction)
			free((*scene)->cams->direction);
		if ((*scene)->cams->origin)
			free((*scene)->cams->origin);
		free((*scene)->cams);
	}
	if ((*scene)->ambient)
		free((*scene)->ambient);
	if ((*scene)->light)
	{
		if ((*scene)->light->point)
			free((*scene)->light->point);
		free((*scene)->light);
	}
	if ((*scene)->elements)
	{
		while ((*scene)->elements)
		{
			if ((int)(*scene)->id == SPHERE)
				free(((t_sphere *)(*scene)->elements->content)->center);
			if ((int)(*scene)->id == CYL)
			{
				free(((t_cylinder *)(*scene)->elements->content)->point);
				free(((t_cylinder *)(*scene)->elements->content)->or_vec);
			}
			tmp = (*scene)->elements;
			(*scene)->elements = (*scene)->elements->next;
			free(tmp);
			tmp = (*scene)->id;
			(*scene)->id = (*scene)->id->next;
			free(tmp);
		}

	}
}
