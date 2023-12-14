/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:02:52 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 17:54:40 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Plane.h"
#include "Scene.h"
#include "libft.h"
#include "Sphere.h" // delete when refactor is done

// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
void	plane_func_init(t_plane *this)
{
	this->object.intersect = plane_intersect;
	this->object.update_view_mat = plane_update_view_mat;
	this->object.init_world_coord = plane_init_world_coord;
	this->object.trace_ray = trace_ray;
}

// float denom = normal.dot(ray.direction);
// if (abs(denom) > 0.0001f) // your favorite epsilon
// {
//     float t = (center - ray.origin).dot(normal) / denom;
//     if (t >= 0) return true; // you might want to allow an epsilon here too
// }
// return false;

t_hit	plane_intersect(t_object *this, t_ray ray)
{
	t_hit				hit;
	float				t;
	float				denom;
	t_vector			point;
	t_plane *const		plane = (t_plane *)this;

	hit.distance = -1.f;
	hit.obj = this;
	denom = vector_dot(ray.dir, plane->normal_view);
	if (ft_fabs(denom) < EPSILON)
		return (hit);
	t = vector_dot(vector_sub(plane->object.view_pos, ray.origin),
			plane->normal_view) / denom;
	if (t < 0)
		return (hit);
	point = pos_add(ray.origin, scalar_mul(t, ray.dir));
	hit.point = point;
	hit.distance = t;
	hit.color = this->color;
	hit.normal = plane->normal_view;
	return (hit);
}

void	plane_init_world_coord(t_object *this)
{
	(void)this;
	return ;
}

void	plane_update_view_mat(t_object *this, t_matrix *tr_view_mat)
{
	t_plane *const	plane = (t_plane *)this;

	this->tr_view_mat = *tr_view_mat;
	transform(&this->view_pos, &this->pos, tr_view_mat);
	transform(&plane->normal_view, &plane->normal, tr_view_mat);
	return ;
}

// t_hit	plane_trace_ray(t_object *this, t_ray ray, int recursion_num)
// {
// 	t_hit		hit;
// 	t_hit		reflect_hit;
// 	t_vector	specular;

// 	hit.distance = -1.f;
// 	hit = plane_intersect(this, ray);
// 	if (hit.distance < 0.f)
// 		return (hit);
// 	hit.color = scalar_mul(
// 			1.f - this->reflect_ratio,
// 			vector_clamp(
// 				sphere_get_phong_color(this, ray, hit, &specular), 0.f, 255.f));
// 	hit.color = vector_add(hit.color, specular);
// 	hit.color = vector_clamp(hit.color, 0.f, 255.f);
// 	if (recursion_num <= 0)
// 		return (hit);
// 	reflect_hit
// 		= compute_reflect_recursive(this->scene, hit, ray, recursion_num);
// 	if (reflect_hit.distance <= 0)
// 		return (hit);
// 	reflect_hit.color = vector_clamp(reflect_hit.color, 0.f, 255.f);
// 	hit.color = vector_add(hit.color, scalar_mul(
// 				this->reflect_ratio, reflect_hit.color));
// 	hit.color = vector_clamp(hit.color, 0.f, 255.f);
// 	return (hit);
// }
