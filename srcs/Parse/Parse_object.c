/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:50:04 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/18 16:32:57 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Parse.h"
#include "Scene.h"
#include "libft.h"
#include "get_next_line_bonus.h"
#include "Sphere.h"
#include "Triangle.h"

#include <stdio.h> // DEBUG

void	parse_sphere(char *line, t_scene *scene)
{
	char **const	split = ft_split(line, ' ');
	char **const	pos_split = ft_split(split[1], ',');
	char **const	rgb_split = ft_split(split[3], ',');
	t_sphere *const	sphere = (t_sphere *)malloc(sizeof(t_sphere));

	if (split[0] == NULL || split[1] == NULL || split[2] == NULL
		|| split[3] == NULL || split[4] != NULL
		|| pos_split[0] == NULL || pos_split[1] == NULL || pos_split[2] == NULL
		|| pos_split[3] != NULL
		|| rgb_split[0] == NULL || rgb_split[1] == NULL || rgb_split[2] == NULL
		|| rgb_split[3] != NULL)
		exit_parse(line);
	sphere->object.pos = make_vector(ft_atof(pos_split[0]),
			ft_atof(pos_split[1]), ft_atof(pos_split[2]), 1.f);
	sphere->radius = ft_atof(split[2]);
	sphere->object.scene = scene;
	sphere->object.norm_rotation = make_vector(0.f, 0.f, -1.f, 0.f);
	sphere->object.reachable_max_radius = sphere->radius;
	sphere_func_init(sphere);
	sphere->object.color = make_vector(ft_atof(rgb_split[0]),
			ft_atof(rgb_split[1]), ft_atof(rgb_split[2]), 1.f);
	add_object(scene, (t_object *)sphere);
	free_split(pos_split);
	printf("malloc shpere %p\n", sphere);
}

static t_vector	get_barycentric_point(t_vector v1, t_vector v2, t_vector v3)
{
	t_vector	barycentric_point;

	barycentric_point.x = (v1.x + v2.x + v3.x) / 3.f;
	barycentric_point.y = (v1.y + v2.y + v3.y) / 3.f;
	barycentric_point.z = (v1.z + v2.z + v3.z) / 3.f;
	barycentric_point.w = 1.f;
	return (barycentric_point);
}

void	parse_triangle_rgb(t_triangle *triangle, char **sp, t_scene *scene)
{
	char	**rgb_split;

	triangle->object.scene = scene;
	rgb_split = ft_split(sp[4], ',');
	if (rgb_split[0] == NULL || rgb_split[1] == NULL || rgb_split[2] == NULL
		|| rgb_split[3] != NULL)
		exit_parse(sp[4]);
	triangle->object.color = make_vector(ft_atof(rgb_split[0]),
			ft_atof(rgb_split[1]), ft_atof(rgb_split[2]), 1.f);
	free_split(rgb_split);
	free_split(sp);
}

void	set_triangle_element(
	t_triangle *triangle, char **v1, char **v2, char **v3)
{
	triangle->v[0] = pos_sub(
			make_vector(ft_atof(v1[0]), ft_atof(v1[1]), ft_atof(v1[2]), 1.f),
			triangle->object.pos);
	triangle->v[1] = pos_sub(
			make_vector(ft_atof(v2[0]), ft_atof(v2[1]), ft_atof(v2[2]), 1.f),
			triangle->object.pos);
	triangle->v[2] = pos_sub(
			make_vector(ft_atof(v3[0]), ft_atof(v3[1]), ft_atof(v3[2]), 1.f),
			triangle->object.pos);
	triangle->object.reachable_max_radius = ft_max3f(
			vector_length(triangle->v[0]),
			vector_length(triangle->v[1]),
			vector_length(triangle->v[2]));
	triangle_func_init(triangle);
	free_split(v1);
	free_split(v2);
	free_split(v3);
}

void	parse_triangle(char *line, t_scene *scene)
{
	char **const		sp = ft_split(line, ' ');
	char **const		v1 = ft_split(sp[1], ',');
	char **const		v2 = ft_split(sp[2], ',');
	char **const		v3 = ft_split(sp[3], ',');
	t_triangle *const	triangle = (t_triangle *)malloc(sizeof(t_triangle));

	if (!sp[0] || !sp[1] || !sp[2] || !sp[3] || !sp[4] || sp[5] || !v1[0]
		|| !v1[1] || !v1[2] || v1[3] || !v2[0] || !v2[1] || !v2[2]
		|| v2[3] || !v3[0] || !v3[1] || !v3[2] || v3[3])
		exit_parse(line);
	triangle->object.pos = get_barycentric_point(
			make_vector(ft_atof(v1[0]), ft_atof(v2[0]), ft_atof(v3[0]), 1.f),
			make_vector(ft_atof(v1[1]), ft_atof(v2[1]), ft_atof(v3[1]), 1.f),
			make_vector(ft_atof(v1[2]), ft_atof(v2[2]), ft_atof(v3[2]), 1.f));
	triangle->object.norm_rotation = vector_cross(
			vector_sub(
				make_vector(ft_atof(v2[0]), ft_atof(v2[1]), ft_atof(v2[2]), 1),
				make_vector(ft_atof(v1[0]), ft_atof(v1[1]), ft_atof(v1[2]), 1)),
			vector_sub(
				make_vector(ft_atof(v3[0]), ft_atof(v3[1]), ft_atof(v3[2]), 1),
				make_vector(ft_atof(v1[0]), ft_atof(v1[1]), ft_atof(v1[2]), 1))
			);
	parse_triangle_rgb(triangle, sp, scene);
	set_triangle_element(triangle, v1, v2, v3);
	add_object(scene, (t_object *)triangle);
}
