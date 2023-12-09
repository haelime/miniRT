/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:39:21 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/09 16:38:55 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"

void	init_render_scene(t_scene *scene)
{
	int		i;

	i = 0;
	while (i < scene->object_num)
	{
		scene->objects[i]->init_world_coord(scene->objects[i]);
		i++;
	}
}

t_matrix	make_trans_mat(t_vector pos)
{
	t_matrix	tr_mat;

	make_diagonal_matrix(&tr_mat, make_vector(1.f, 1.f, 1.f, 1.f));
	tr_mat.m[3][0] = -pos.x;
	tr_mat.m[3][1] = -pos.y;
	tr_mat.m[3][2] = -pos.z;
	return (tr_mat);
}

t_matrix	make_tr_rot_x_mat(float angle)
{
	t_matrix	rot_x_mat;

	make_diagonal_matrix(&rot_x_mat, make_vector(1.f, 1.f, 1.f, 1.f));
	rot_x_mat.m[1][1] = cos(angle * M_PI);
	rot_x_mat.m[1][2] = sin(angle * M_PI);
	rot_x_mat.m[2][1] = -sin(angle * M_PI);
	rot_x_mat.m[2][2] = cos(angle * M_PI);
	return (rot_x_mat);
}

t_matrix	make_tr_rot_y_mat(float angle)
{
	t_matrix	tr_rot_y_mat;

	make_diagonal_matrix(&tr_rot_y_mat, make_vector(1.f, 1.f, 1.f, 1.f));
	tr_rot_y_mat.m[0][0] = cos(angle * M_PI);
	tr_rot_y_mat.m[0][2] = -sin(angle * M_PI);
	tr_rot_y_mat.m[2][0] = sin(angle * M_PI);
	tr_rot_y_mat.m[2][2] = cos(angle * M_PI);
	return (tr_rot_y_mat);
}

t_matrix	make_tr_rot_z_mat(float angle)
{
	t_matrix	tr_rot_z_mat;

	make_diagonal_matrix(&tr_rot_z_mat, make_vector(1.f, 1.f, 1.f, 1.f));
	tr_rot_z_mat.m[0][0] = cos(angle * M_PI);
	tr_rot_z_mat.m[0][1] = sin(angle * M_PI);
	tr_rot_z_mat.m[1][0] = -sin(angle * M_PI);
	tr_rot_z_mat.m[1][1] = cos(angle * M_PI);
	return (tr_rot_z_mat);
}
