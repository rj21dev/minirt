/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:22:13 by coverand          #+#    #+#             */
/*   Updated: 2022/06/25 00:00:18 by rjada            ###   ########.fr       */
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
	scene->id = NULL;
	scene->width = WIDTH;
	scene->height = HEIGHT;
	return (scene);
}

// int	main(int argc, char **argv)
// {
// 	t_scene	*scene;

// 	if (argc != 2)
// 		ft_errors_handler(ARGS_COUNT_FAILURE);
// 	ft_check_extension(argv[1]);
// 	scene = ft_init();
// 	ft_read_from_file(argv[1], &scene);
// 	ft_clear(&scene);
// 	return (0);
// }
