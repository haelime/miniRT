/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:44:39 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/28 20:40:47 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Triangle.h"
#include "Scene.h"
#include "libft.h"
#include <stdbool.h>

#include "Sphere.h"

void	triangle_func_init(t_triangle *this)
{
	this->object.intersect = triangle_intersect;
	// this->object.update_rotation = triangle_update_rotation;
	this->object.update_view_mat = triangle_update_view_mat;
	// this->object.update_pos = triangle_update_pos;
	this->object.init_world_coord = triangle_init_world_coord;
	this->object.trace_ray = triangle_trace_ray;
}

t_hit	triangle_trace_ray(t_object *this, t_ray ray, int recursion_num)
{
	t_hit		hit;
	t_hit		reflect_hit;
	t_vector	specular;

	hit.distance = -1.f;
	hit = triangle_intersect(this, ray);
	if (hit.distance < 0.f)
		return (hit);
	hit.color = scalar_mul(
			1.f - this->reflect_ratio,
			vector_clamp(
				sphere_get_phong_color(this, ray, hit, &specular), 0.f, 255.f));
	hit.color = vector_add(hit.color, specular);
	hit.color = vector_clamp(hit.color, 0.f, 255.f);
	if (recursion_num <= 0)
		return (hit);
	reflect_hit
		= compute_reflect_recursive(this->scene, hit, ray, recursion_num);
	if (reflect_hit.distance <= 0)
		return (hit);
	reflect_hit.color = vector_clamp(reflect_hit.color, 0.f, 255.f);
	hit.color = vector_add(
			hit.color,
			scalar_mul(
				this->reflect_ratio,
				reflect_hit.color));
	hit.color = vector_clamp(hit.color, 0.f, 255.f);
	return (hit);
}

void	triangle_update_view_mat(t_object *this, t_matrix *tr_view_mat)
{
	t_triangle *const	tri = (t_triangle *)this;

	this->tr_view_mat = *tr_view_mat;
	transform(&tri->v_view[0], &tri->v_world[0], tr_view_mat);
	transform(&tri->v_view[1], &tri->v_world[1], tr_view_mat);
	transform(&tri->v_view[2], &tri->v_world[2], tr_view_mat);
	transform(&tri->normal, &this->pos, tr_view_mat);

	return ; 
}
void	triangle_init_world_coord(t_object *this)
{
	t_triangle *const	tri = (t_triangle *)this;

	tri->v_world[0] = pos_add(tri->v[0], tri->object.pos);
	tri->v_world[1] = pos_add(tri->v[1], tri->object.pos);
	tri->v_world[2] = pos_add(tri->v[2], tri->object.pos);

	tri->normal = vector_normalize(vector_cross(vector_sub(tri->v_view[1], tri->v_view[0]), vector_sub(tri->v_view[2], tri->v_view[0])));

	return ;
}

static bool	is_inside_triangle(t_vector point, t_triangle *tri, t_hit hit)
{
	const t_vector	norm1 = vector_normalize(vector_cross(vector_sub(
					point, tri->v_view[2]),
				vector_sub(tri->v_view[1], tri->v_view[2])));
	const t_vector	norm2 = vector_normalize(vector_cross(vector_sub(
					point, tri->v_view[0]),
				vector_sub(tri->v_view[2], tri->v_view[0])));
	const t_vector	norm3 = vector_normalize(vector_cross(vector_sub(
					tri->v_view[1], tri->v_view[0]),
				vector_sub(point, tri->v_view[0])));

	if (vector_dot(norm1, tri->normal) < 0.f
		|| vector_dot(norm2, tri->normal) < 0.f
		|| vector_dot(norm3, tri->normal) < 0.f)
		return (false);
	return (true);
}

t_hit triangle_intersect(t_object *this, t_ray ray)
{
    t_hit hit;
    float t;
    t_vector point;
    t_triangle *const tri = (t_triangle *)this;

    hit.distance = 0.f; // 초기값 변경
    hit.obj = this;

    // EPSILON을 이용한 부동소수점 비교 추가
    if (ft_fabs(vector_dot(ray.dir, tri->normal)) < EPSILON)
        return hit;

    t = (vector_dot(tri->v_view[0], tri->normal)
         - vector_dot(ray.origin, tri->normal))
        / vector_dot(ray.dir, tri->normal);

    if (t < EPSILON) // 0 대신 EPSILON 사용
        return hit;

    point = pos_add(ray.origin, scalar_mul(t, ray.dir));

    if (is_inside_triangle(point, tri, hit))
    {
        hit.point = point;
        // 거리 계산을 t 값 사용하여 수정
        hit.distance = t;
        hit.color = this->color;
        hit.normal = tri->normal;
    }
    return hit;
}

