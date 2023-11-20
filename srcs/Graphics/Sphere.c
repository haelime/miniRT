/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:43:42 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/20 19:10:00 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Sphere.h"
#include "Scene.h"

#include <stdio.h> // DEBUG

void	sphere_func_init(t_sphere *this)
{
	this->object.trace_ray = sphere_trace_ray;
	this->object.intersect = sphere_intersect;
	this->object.update_rotation = sphere_update_rotation;
	this->object.update_pos = sphere_update_pos;
	this->object.update_view_mat = sphere_update_view_mat;
}

void	sphere_update_rotation(t_object *this, t_vector rot)
{
	this->norm_rotation = rot;
	return ;
}

void	sphere_update_pos(t_object *this, t_vector pos)
{
	this->pos = pos;
	make_diagonal_matrix(&this->tr_pos_mat, pos);
	transform(&this->view_pos, &this->pos, &this->tr_view_mat);
	return ;
}

void	sphere_update_view_mat(t_object *this, t_matrix *tr_view_mat)
{
	this->tr_view_mat = *tr_view_mat;
	transform(&this->view_pos, &this->pos, tr_view_mat);
	return ;
}
