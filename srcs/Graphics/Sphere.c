/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:43:42 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/20 19:45:48 by hyunjunk         ###   ########.fr       */
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
	this->object.init_world_coord = sphere_init_world_coord;
	this->object.update_view_mat = sphere_update_view_mat;
}

void	sphere_init_world_coord(t_object *this)
{
	return ;
}

void	sphere_update_view_mat(t_object *this, t_matrix *tr_view_mat)
{
	this->tr_view_mat = *tr_view_mat;
	transform(&this->view_pos, &this->pos, tr_view_mat);
	return ;
}
