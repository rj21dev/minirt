/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:22:13 by coverand          #+#    #+#             */
/*   Updated: 2022/06/22 16:38:23 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_check_extension(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot)
		ft_errors_handler(WRONG_EXTENSION);
	if (strcmp(dot, ".rt"))
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
		if (line && strcmp(line, "\n"))
		{
			elements = ft_split(line, ' ');
			ft_get_elements(elements, scene);
		}
		ft_clear_split(elements);
		free(line);
		line = get_next_line(fd);
	}
	// if (*scene)
	// {
	// 	if ((*scene)->ambient)
	// 		printf("A %.1f, %i,%i,%i\n", (*scene)->ambient->lighting_ratio, \
	// 		(*scene)->ambient->color.r, (*scene)->ambient->color.g, \
	// 		(*scene)->ambient->color.b);
	// 	if ((*scene)->cams)
	// 		printf("C %.1f,%.1f,%.1f %.1f,%.1f,%.1f %.1f\n", (*scene)->cams->origin->x, \
	// 		(*scene)->cams->origin->y, (*scene)->cams->origin->z, \
	// 		(*scene)->cams->direction->x, (*scene)->cams->direction->y, \
	// 		(*scene)->cams->direction->z, (*scene)->cams->fov);
	// 	if ((*scene)->light)
	// 		printf("L %.1f,%.1f,%.1f %.1f %i,%i,%i\n", (*scene)->light->point->x, \
	// 		(*scene)->light->point->y, (*scene)->light->point->z, \
	// 		(*scene)->light->brightness_ratio, (*scene)->light->color.r, \
	// 		(*scene)->light->color.g, (*scene)->light->color.b);
	// 	if ((*scene)->elements)
	// 	{
	// 		t_list *tmp = (*scene)->elements;
	// 		printf("size: %i\n", ft_lstsize((void *)tmp));
	// 		int i = 0;
	// 		while ((*scene)->elements)
	// 		{
	// 			if (i == 0)
	// 				printf("radius: %f\n", ((t_sphere *)((*scene)->elements->content))->radius);
	// 			if (i == 1)
	// 				printf("diam: %f\n", ((t_cylinder *)((*scene)->elements->content))->diameter);
	// 			(*scene)->elements = (*scene)->elements->next;
	// 			i++;
	// 		}
	// 	}
	// }
	close(fd);
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
	return (scene);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		ft_errors_handler(ARGS_COUNT_FAILURE);
	ft_check_extension(argv[1]);
	scene = ft_init();
	ft_read_from_file(argv[1], &scene);
	ft_clear(&scene);
	return (0);
}
