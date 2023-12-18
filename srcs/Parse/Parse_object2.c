/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_object2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:02:17 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/18 16:33:06 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "Parse.h"
#include "Scene.h"
#include "libft.h"
#include "get_next_line_bonus.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Circle.h"

void	free_splits(char **const*pos_split, char **const*norm_split,
	char **const*rgb_split, char **const*split)
{
	free_split(*pos_split);
	free_split(*norm_split);
	free_split(*rgb_split);
	free_split(*split);
}

void	parse_plane(char *line, t_scene *scene)
{
	char **const	split = ft_split(line, ' ');
	char **const	pos_split = ft_split(split[1], ',');
	char **const	norm_split = ft_split(split[2], ',');
	char **const	rgb_split = ft_split(split[3], ',');
	t_plane *const	plane = (t_plane *)malloc(sizeof(t_plane));

	if (split[0] == NULL || split[1] == NULL || split[2] == NULL
		|| split[3] == NULL || split[4] != NULL
		|| pos_split[0] == NULL || pos_split[1] == NULL || pos_split[2] == NULL
		|| pos_split[3] != NULL || norm_split[0] == NULL
		|| norm_split[1] == NULL || norm_split[2] == NULL
		|| norm_split[3] != NULL || rgb_split[0] == NULL
		|| rgb_split[1] == NULL || rgb_split[2] == NULL || rgb_split[3] != NULL)
		exit_parse(line);
	plane->object.pos = make_vector(ft_atof(pos_split[0]),
			ft_atof(pos_split[1]), ft_atof(pos_split[2]), 1.f);
	plane->object.scene = scene;
	plane->normal = make_vector(ft_atof(norm_split[0]),
			ft_atof(norm_split[1]), ft_atof(norm_split[2]), 0.f);
	plane_func_init(plane);
	plane->object.color = make_vector(ft_atof(rgb_split[0]),
			ft_atof(rgb_split[1]), ft_atof(rgb_split[2]), 1.f);
	add_object(scene, (t_object *)plane);
	free_splits(&pos_split, &norm_split, &rgb_split, &split);
	printf("malloc plane %p\n", plane);
}

void	add_circles(t_scene *scene, t_cylinder *cylinder)
{
	t_circle *const	circle1 = (t_circle *)malloc(sizeof(t_circle));
	t_circle *const	circle2 = (t_circle *)malloc(sizeof(t_circle));

	circle1->object.scene = scene;
	circle1->normal = cylinder->normal;
	circle_func_init(circle1);
	circle1->radius = cylinder->radius;
	circle1->object.color = cylinder->object.color;
	circle1->object.pos = pos_add(cylinder->object.pos,
			scalar_mul(cylinder->height / 2, cylinder->normal));
	circle2->object.scene = scene;
	circle2->normal = cylinder->normal;
	circle_func_init(circle2);
	circle2->radius = cylinder->radius;
	circle2->object.color = cylinder->object.color;
	circle2->object.pos = pos_add(cylinder->object.pos,
			scalar_mul(-cylinder->height / 2, cylinder->normal));
	add_object(scene, (t_object *)circle1);
	add_object(scene, (t_object *)circle2);
}

// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// identifier: cy
// x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// 3d normalized vector of axis of cylinder.
// In range [-1,1] for each x,y,z axis:
// 0,0.0,1.0
// the cylinder diameter: 14.2
// the cylinder height: 21.42
// R,G,B colors in range [0,255]: 10, 0, 255
static bool	is_valid_split(char **const split, char **const pos_split,
	char **const norm_split, char **const rgb_split)
{
	if (split[0] == NULL || split[1] == NULL || split[2] == NULL
		|| split[3] == NULL || split[4] == NULL || split[5] == NULL
		|| split[6] != NULL || pos_split[0] == NULL || pos_split[1] == NULL
		|| pos_split[2] == NULL || pos_split[3] != NULL || norm_split[0] == NULL
		|| norm_split[1] == NULL || norm_split[2] == NULL
		|| norm_split[3] != NULL || rgb_split[0] == NULL || rgb_split[1] == NULL
		|| rgb_split[2] == NULL || rgb_split[3] != NULL)
		return (false);
	return (true);
}

void	parse_cylinder(char *line, t_scene *scene)
{
	char **const		split = ft_split(line, ' ');
	char **const		pos_split = ft_split(split[1], ',');
	char **const		norm_split = ft_split(split[2], ',');
	char **const		rgb_split = ft_split(split[5], ',');
	t_cylinder *const	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));

	if (is_valid_split(split, pos_split, norm_split, rgb_split) == false)
		exit_parse(line);
	cylinder->object.pos = make_vector(ft_atof(pos_split[0]),
			ft_atof(pos_split[1]), ft_atof(pos_split[2]), 1.f);
	cylinder->object.scene = scene;
	cylinder->normal = make_vector(ft_atof(norm_split[0]),
			ft_atof(norm_split[1]), ft_atof(norm_split[2]), 0.f);
	cylinder_func_init(cylinder);
	cylinder->radius = ft_atof(split[3]);
	cylinder->height = ft_atof(split[4]);
	cylinder->object.color = make_vector(ft_atof(rgb_split[0]),
			ft_atof(rgb_split[1]), ft_atof(rgb_split[2]), 1.f);
	add_object(scene, (t_object *)cylinder);
	add_circles(scene, cylinder);
	free_splits(&pos_split, &norm_split, &rgb_split, &split);
	printf("malloc cylinder %p\n", cylinder);
}
