/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:43:42 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/09 16:17:08 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Sphere.h"
#include "Scene.h"

#include <stdio.h> // DEBUG

void	sphere_func_init(t_sphere *this)
{
	this->object.trace_ray = trace_ray;
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

t_hit	sphere_intersect(t_object *this, t_ray ray)
{
	t_hit		hit;
	float		b;
	float		c;
	float		nabla;
	float		dis2;

	hit.distance = -1.f;
	hit.obj = this;
	b = 2.f * vector_dot(ray.dir, vector_sub(ray.origin, this->view_pos));
	c = vector_dot(vector_sub(ray.origin, this->view_pos),
			vector_sub(ray.origin, this->view_pos))
		- ((t_sphere *)this)->radius * ((t_sphere *)this)->radius;
	nabla = b * b / 4.f - c;
	if (nabla < EPSILON)
		return (hit);
	hit.distance = (-b / 2.f) + sqrtf(nabla);
	dis2 = (-b / 2.f) - sqrtf(nabla);
	if ((hit.distance > dis2 && dis2 >= 0.f) || hit.distance < 0.f)
		hit.distance = dis2;
	hit.point = pos_add(ray.origin, scalar_mul(hit.distance, ray.dir));
	hit.normal = vector_normalize(vector_sub(hit.point, this->view_pos));
	hit.color = this->color;
	return (hit);
}
