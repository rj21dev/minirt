/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:22:13 by coverand          #+#    #+#             */
/*   Updated: 2022/07/05 19:12:43 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_check_extension(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot)
		ft_errors_handler(WRONG_EXTENSION);
	if (ft_strcmp(dot, ".rt"))
		ft_errors_handler(WRONG_EXTENSION);
}

void	ft_read_from_file(char *filename, t_scene **scene)
{
	int		fd;
	char	*line;
	char	**elements;

	elements = NULL;
	fd = open(filename, O_RDWR);
	if (fd < 0)
		ft_errors_handler(strerror(errno));
	line = get_next_line(fd);
	while (line)
	{
		elements = ft_split(line, ' ');
		ft_get_elements(elements, scene);
		ft_split_free(elements);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!(*scene)->cams || !(*scene)->ambient || !(*scene)->light)
		ft_errors_handler("Missing object (Camera/Ambient lightning/Light)");
}

t_scene	*ft_init(void)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		ft_errors_handler(strerror(errno));
	scene->cams = NULL;
	scene->ambient = NULL;
	scene->light = NULL;
	scene->elements = NULL;
	scene->width = WIDTH;
	scene->height = HEIGHT;
	scene->shift = new_v3(0, 0, 0);
	scene->obj = NULL;
	scene->cyl_height = 0;
	scene->shift_object = 0;
	scene->x = 0;
	scene->y = 0;
	scene->rotation = 1;
	return (scene);
}
