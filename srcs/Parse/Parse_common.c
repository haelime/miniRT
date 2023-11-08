/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:17:49 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 16:44:04 by hyunjunk         ###   ########.fr       */
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
	if (split[3] != NULL)
		exit_parse(line);
	scene->resolution.x = ft_atoi(split[1]);
	scene->resolution.y = ft_atoi(split[2]);
	free_split(split);
}

void	parse_ambient(char *line, t_scene *scene)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[3] != NULL)
		exit_parse(line);
	scene->ambient.x = ft_atof(split[1]);
	scene->ambient.y = ft_atof(split[2]);
	scene->ambient.z = ft_atof(split[3]);
	free_split(split);
}

void	parse_camera(char *line, t_scene *scene)
{
	char		**split;
	t_camera	*camera;

	split = ft_split(line, ' ');
	if (split[4] != NULL)
		exit_parse(line);
	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->origin.x = ft_atof(split[1]);
	camera->origin.y = ft_atof(split[2]);
	camera->origin.z = ft_atof(split[3]);
	camera->normal.x = ft_atof(split[4]);
	camera->normal.y = ft_atof(split[5]);
	camera->normal.z = ft_atof(split[6]);
	camera->fov = ft_atof(split[7]);
	camera->next = scene->camera;
	scene->camera = camera;
	free_split(split);
}

void	parse_light(char *line, t_scene *scene)
{
	char	**split;
	t_light	*light;

	split = ft_split(line, ' ');
	if (split[4] != NULL)
		exit_parse(line);
	light = (t_light *)malloc(sizeof(t_light));
	light->center.x = ft_atof(split[1]);
	light->center.y = ft_atof(split[2]);
	light->center.z = ft_atof(split[3]);
	light->intensity = ft_atof(split[4]);
	light->color.x = ft_atof(split[5]);
	light->color.y = ft_atof(split[6]);
	light->color.z = ft_atof(split[7]);
	scene->lights = light;
	free_split(split);
}
