/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:17:49 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/18 16:32:43 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Parse.h"
#include "Scene.h"
#include "libft.h"
#include "get_next_line_bonus.h"

void	parse_resolution(char *line, t_scene *scene)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[0] == NULL || split[1] == NULL || split[2] == NULL
		|| split[3] != NULL)
		exit_parse(line);
	scene->resolution.x = ft_atoi(split[1]);
	scene->resolution.y = ft_atoi(split[2]);
	scene->resolution.z = 0;
	scene->resolution.w = 0;
	free_split(split);
}

void	parse_ambient(char *line, t_scene *scene)
{
	char	**split;
	char	**rgb_split;

	split = ft_split(line, ' ');
	if (split[0] == NULL || split[1] == NULL || split[2] == NULL
		|| split[3] != NULL)
		exit_parse(line);
	scene->ambient_ratio = ft_atof(split[1]);
	rgb_split = ft_split(split[2], ',');
	if (rgb_split[0] == NULL || rgb_split[1] == NULL || rgb_split[2] == NULL
		|| rgb_split[3] != NULL)
		exit_parse(line);
	scene->ambient.x = ft_atof(rgb_split[0]);
	scene->ambient.y = ft_atof(rgb_split[1]);
	scene->ambient.z = ft_atof(rgb_split[2]);
	scene->ambient.w = 1.f;
	free_split(rgb_split);
	free_split(split);
}

void	parse_camera(char *line, t_scene *scene)
{
	char **const	split = ft_split(line, ' ');
	char **const	pos_split = ft_split(split[1], ',');
	char **const	norm_split = ft_split(split[2], ',');

	if (split[0] == NULL || split[1] == NULL || split[2] == NULL
		|| split[3] == NULL || split[4] != NULL
		|| pos_split[0] == NULL || pos_split[1] == NULL || pos_split[2] == NULL
		|| pos_split[3] != NULL
		|| norm_split[0] == NULL || norm_split[1] == NULL
		|| norm_split[2] == NULL || norm_split[3] != NULL)
		exit_parse(line);
	scene->camera = (t_camera *)malloc(sizeof(t_camera));
	scene->camera->pos = make_vector(ft_atof(pos_split[0]),
			ft_atof(pos_split[1]), ft_atof(pos_split[2]), 1.f);
	scene->camera->norm_rotation = make_vector(ft_atof(norm_split[0]),
			ft_atof(norm_split[1]), ft_atof(norm_split[1]), 0.f);
	scene->camera->fov = ft_atof(split[3]);
	free_split(pos_split);
	free_split(norm_split);
	free_split(split);
}

void	parse_light(char *line, t_scene *scene)
{
	char **const	split = ft_split(line, ' ');
	char **const	pos_split = ft_split(split[1], ',');
	char **const	rgb_split = ft_split(split[3], ',');
	t_light *const	light = (t_light *)malloc(sizeof(t_light));

	if (split[0] == NULL || split[1] == NULL || split[2] == NULL
		|| split[3] == NULL || split[4] != NULL
		|| pos_split[0] == NULL || pos_split[1] == NULL || pos_split[2] == NULL
		|| pos_split[3] != NULL
		|| rgb_split[0] == NULL || rgb_split[1] == NULL || rgb_split[2] == NULL
		|| rgb_split[3] != NULL)
		exit_parse(line);
	light->pos = make_vector(ft_atof(pos_split[0]),
			ft_atof(pos_split[1]), ft_atof(pos_split[2]), 1.f);
	light->intensity = ft_atof(split[2]);
	light->color = make_vector(ft_atof(rgb_split[0]),
			ft_atof(rgb_split[1]), ft_atof(rgb_split[2]), 1.f);
	add_light(scene, light);
	free_split(pos_split);
	free_split(rgb_split);
	free_split(split);
}
