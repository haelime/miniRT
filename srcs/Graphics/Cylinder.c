/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:34:49 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 16:20:44 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Cylinder.h"
#include "Scene.h"
#include "Phong.h"

// typedef struct s_cylinder
// {
// 	t_object		object;
// 	double			radius;
// 	double			diameter;
// 	double			height;

// 	t_vector		v_world;
// 	t_vector		v_view;
// 	t_vector		normal_view;
// }				t_cylinder;
void	cylinder_func_init(t_cylinder *this)
{
	this->object.trace_ray = trace_ray;
	this->object.intersect = cylinder_intersect;
	this->object.init_world_coord = cylinder_init_world_coord;
	this->object.update_view_mat = cylinder_update_view_mat;
}

void	cylinder_init_world_coord(t_object *this)
{
	t_cylinder *const	cylinder = (t_cylinder *)this;

	cylinder->normal = vector_normalize(cylinder->normal);
	return ;
}

void	cylinder_update_view_mat(t_object *this, t_matrix *tr_view_mat)
{
	t_cylinder *const	cylinder = (t_cylinder *)this;

	this->tr_view_mat = *tr_view_mat;
	transform(&this->view_pos, &this->pos, tr_view_mat);
	transform(&cylinder->normal_view, &cylinder->normal, tr_view_mat);
}
