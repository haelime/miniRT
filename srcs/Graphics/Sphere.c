/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:43:42 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 21:42:39 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Sphere.h"

void	sphere_func_init(t_sphere *this)
{
	this->object.intersect = sphere_intersect;
	this->object.update_rotation = sphere_update_rotation;
	this->object.update_pos = sphere_update_pos;
}

t_hit	sphere_intersect(
	t_object *this, t_vector origin, t_vector ray, t_matrix *tr_view_mat)
{
	t_vector	view_pos;
	t_hit		hit;
	float		b;
	float		c;
	float		nabla;

	hit.distance = -1.f;
	transform(&view_pos, &this->pos, tr_view_mat);
	b = 2.f * vector_dot(ray, vector_sub(origin, view_pos));
	c = vector_dot(vector_sub(origin, view_pos),
			vector_sub(origin, view_pos))
		- ((t_sphere *)this)->radius * ((t_sphere *)this)->radius;
	nabla = b * b / 4.f - c;
	if (nabla < 0.f)
		return (hit);
	hit.distance = (-b / 2.f) + sqrtf(nabla);
	if (hit.distance > (-b / 2.f) - sqrtf(nabla))
		hit.distance = (-b / 2.f) - sqrtf(nabla);
	hit.point = pos_add(origin, scalar_mul(hit.distance, ray));
	hit.normal = vector_normalize(vector_sub(hit.point, view_pos));
	hit.color = this->color; // TODO: recursive
	return (hit);
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
	return ;
}
