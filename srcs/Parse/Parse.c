/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:51:07 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/12 20:31:28 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Parse.h"
#include "Scene.h"
#include "libft.h"
#include "get_next_line.h"

void	exit_parse(char *line)
{
	free(line);
	write(1, "Error\n", 6);
	exit(0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char		*get_next_line(int fd);
void		parse_common(char *line, t_scene *scene);
void		parse_object(char *line, t_scene *scene);
void		parse_resolution(char *line, t_scene *scene);
void		parse_ambient(char *line, t_scene *scene);
void		parse_camera(char *line, t_scene *scene);
void		parse_light(char *line, t_scene *scene);
void		parse_sphere(char *line, t_scene *scene);
void		parse_plane(char *line, t_scene *scene);
void		parse_square(char *line, t_scene *scene);
void		parse_cylinder(char *line, t_scene *scene);
void		parse_triangle(char *line, t_scene *scene);

void	parse(char *file, t_scene *scene)
{
	const int	fd = open(file, O_RDONLY);
	char		*line;

	if (fd < 0)
		exit_parse(NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "R ", 2) == 0 || ft_strncmp(line, "A ", 2) == 0
			|| ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "L ", 2) == 0)
			parse_common(line, scene);
		else if (ft_strncmp(line, "sp ", 3) == 0
			|| ft_strncmp(line, "pl ", 3) == 0
			|| ft_strncmp(line, "sq ", 3) == 0
			|| ft_strncmp(line, "cy ", 3) == 0
			|| ft_strncmp(line, "tr ", 3) == 0)
			parse_object(line, scene);
		free(line);
		line = NULL;
	}
	close(fd);
}

void	parse_common(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		parse_resolution(line, scene);
	else if (ft_strncmp(line, "A ", 2) == 0)
		parse_ambient(line, scene);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_camera(line, scene);
	else if (ft_strncmp(line, "L ", 2) == 0)
		parse_light(line, scene);
}

void	parse_object(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "sp ", 3) == 0)
		parse_sphere(line, scene);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		parse_plane(line, scene);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		parse_cylinder(line, scene);
	else if (ft_strncmp(line, "tr ", 3) == 0)
		parse_triangle(line, scene);
}
