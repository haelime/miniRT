/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:08:36 by haeem             #+#    #+#             */
/*   Updated: 2023/12/07 18:00:40 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Circle.h"
#include "libft.h"

// typedef struct s_circle
// {
// 	t_object	object;
// 	t_vector	v_world;
// 	t_vector	v_view;
// 	t_vector	normal_view;
// }t_circle;


void	circle_func_init(t_circle *this)
{
	this->object.trace_ray = trace_ray;
	this->object.intersect = circle_intersect;
	this->object.init_world_coord = circle_init_world_coord;
	this->object.update_view_mat = circle_update_view_mat;
}

t_hit	circle_intersect(t_object *this, t_ray ray)
{
	t_hit				hit;
	float				t;
	float				denom;
	t_vector			point;
	t_circle *const		circle = (t_circle *)this;

	hit.distance = -1.f;
	hit.obj = this;
	denom = vector_dot(ray.dir, circle->object.norm_rotation);
	if (ft_fabs(denom) < EPSILON)
		return (hit);
	t = vector_dot(vector_sub(circle->object.view_pos, ray.origin),
			circle->object.norm_rotation) / denom;
	if (t < 0)
		return (hit);
	point = pos_add(ray.origin, scalar_mul(t, ray.dir));

	if (vector_dot(vector_sub(point, circle->object.view_pos), vector_sub(point, circle->object.view_pos)) > circle->radius * circle->radius)
		return (hit);
	hit.point = point;
	hit.distance = t;
	hit.color = this->color;
	hit.normal = circle->object.norm_rotation;
	return (hit);
}

void	circle_init_world_coord(t_object *this)
{
	return ;
}

void	circle_update_view_mat(t_object *this, t_matrix *tr_view_mat)
{
	this->tr_view_mat = *tr_view_mat;
	transform(&this->view_pos, &this->pos, tr_view_mat);
}


