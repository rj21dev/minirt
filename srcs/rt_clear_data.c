/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_clear_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:14:09 by coverand          #+#    #+#             */
/*   Updated: 2022/06/22 17:22:57 by coverand         ###   ########.fr       */
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

void	ft_clear_camera(t_scene **scene)
{
	if ((*scene)->cams->direction)
		free((*scene)->cams->direction);
	if ((*scene)->cams->origin)
		free((*scene)->cams->origin);
	free((*scene)->cams);
}

void	ft_clear_light(t_scene **scene)
{
	if ((*scene)->light->point)
		free((*scene)->light->point);
	free((*scene)->light);
}

void	ft_clear_elements(t_scene **scene)
{
	t_list	*tmp;

	while ((*scene)->elements)
	{
		printf("id: %s\n", (char *)((*scene)->id->content));
		if (!ft_strcmp((char *)((*scene)->id->content), SPHERE))
			free(((t_sphere *)(*scene)->elements->content)->center);
		if (!ft_strcmp((char *)((*scene)->id->content), CYL))
		{
			free(((t_cylinder *)(*scene)->elements->content)->point);
			free(((t_cylinder *)(*scene)->elements->content)->or_vec);
		}
		free((*scene)->id->content);
		free((*scene)->elements->content);
		tmp = (*scene)->elements;
		(*scene)->elements = (*scene)->elements->next;
		free(tmp);
		tmp = (*scene)->id;
		(*scene)->id = (*scene)->id->next;
		free(tmp);
	}
}

void	ft_clear(t_scene **scene)
{
	if (*scene)
	{
		if ((*scene)->cams)
			ft_clear_camera(scene);
		if ((*scene)->ambient)
			free((*scene)->ambient);
		if ((*scene)->light)
			ft_clear_light(scene);
		if ((*scene)->elements)
			ft_clear_elements(scene);
		free(*scene);
	}
}
