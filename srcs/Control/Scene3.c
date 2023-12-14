/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:31:45 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 14:58:44 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Scene.h"
#include "libft.h"
#include "Vector.h"
#include "Matrix.h"

t_matrix	make_tr_view_mat(t_camera *camera)
{
	t_matrix	tr_view_mat;
	t_matrix	tr_rot_x_mat;
	t_matrix	tr_rot_y_mat;
	t_matrix	tr_rot_z_mat;

	tr_view_mat = make_trans_mat(camera->pos);
	tr_rot_x_mat = make_tr_rot_x_mat(camera->norm_rotation.x);
	tr_rot_y_mat = make_tr_rot_y_mat(camera->norm_rotation.y);
	tr_rot_z_mat = make_tr_rot_z_mat(camera->norm_rotation.z);
	concatenate(&tr_view_mat, &tr_view_mat, &tr_rot_x_mat);
	concatenate(&tr_view_mat, &tr_view_mat, &tr_rot_y_mat);
	concatenate(&tr_view_mat, &tr_view_mat, &tr_rot_z_mat);
	transpose(&tr_view_mat);
	return (tr_view_mat);
}

void	transform_scene_camera_coord(t_scene *scene)
{
	int			i;
	t_matrix	tr_view_mat;

	tr_view_mat = make_tr_view_mat(scene->camera);
	i = 0;
	while (i < scene->object_num)
	{
		scene->objects[i]->update_view_mat(scene->objects[i], &tr_view_mat);
		i++;
	}
	i = 0;
	while (i < scene->light_num)
	{
		light_update_view_mat(scene->lights[i], &tr_view_mat);
		i++;
	}
}

int	clamp255(int x)
{
	if (x > 255)
		return (255);
	return (x);
}
