/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_common.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 20:17:49 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/10 15:21:55 by hyunjunk         ###   ########.fr       */
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

/*  A	0.2	255,255,255
구별자 : A
범위 내 주변광 비율 [0.0, 1.0] : 0.2
R,G,B 색 범위 [0, 255] : 255, 255, 255
*/
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

/*  C	-50.0,0,20	0,0,1	70
구별자 : C
시점의 x, y, z 좌표 : 0.0, 0.0, 20.6
정규화된 삼차원 방향 벡터. 각 x, y, z 축 마다 [-1, 1] 의 범위를 가짐 : 0.0, 0.0, 1.0
FOV : 수평 시야 범위 [0, 180]
*/
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
	scene->camera->normal = make_vector(ft_atof(norm_split[0]),
			ft_atof(norm_split[1]), ft_atof(norm_split[1]), 0.f);
	scene->camera->fov = ft_atof(split[3]);
	free_split(pos_split);
	free_split(norm_split);
	free_split(split);
}

/*  L	-40.0,50.0,0.0	0.6	10,0,255
구별자 : L
광원의 x, y, z 좌표 : 0.0, 0.0, 20.6
빛의 밝기 비율 [0.0, 1.0] : 0.6
R,G,B 색 범위 [0, 255] : 10, 0, 255 */
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
