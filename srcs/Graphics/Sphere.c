/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:43:42 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/15 21:00:16 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Sphere.h"
#include "Scene.h"

#include <stdio.h> // DEBUG

void	sphere_func_init(t_sphere *this)
{
	this->object.intersect = sphere_intersect;
	this->object.update_rotation = sphere_update_rotation;
	this->object.update_pos = sphere_update_pos;
	this->object.update_view_mat = sphere_update_view_mat;
}

t_hit	sphere_intersect(t_object *this, t_ray ray, int recursion_num)
{
	t_hit		hit;
	float		b;
	float		c;
	float		nabla;
	t_hit		reflect_hit;

	//printf("intersect this %p\n", this);
	hit.distance = -1.f;
	hit.obj = this;
	b = 2.f * vector_dot(ray.dir, vector_sub(ray.origin, this->view_pos));
	c = vector_dot(vector_sub(ray.origin, this->view_pos),
			vector_sub(ray.origin, this->view_pos))
		- ((t_sphere *)this)->radius * ((t_sphere *)this)->radius;
	nabla = b * b / 4.f - c;
	if (nabla < 0.f)
		return (hit);
	hit.distance = (-b / 2.f) + sqrtf(nabla);
	if (hit.distance > (-b / 2.f) - sqrtf(nabla)
		&& 0.f <= (-b / 2.f) - sqrtf(nabla) && (-b / 2.f) - sqrtf(nabla) >= 0.f)
		hit.distance = (-b / 2.f) - sqrtf(nabla);
	hit.point = pos_add(ray.origin, scalar_mul(hit.distance, ray.dir));
	hit.normal = vector_normalize(vector_sub(hit.point, this->view_pos));
	reflect_hit
		= compute_reflect_recursive(this->scene, hit, ray, recursion_num);
	hit.color = scalar_mul(1.f - hit.obj->reflect_ratio, this->color);
	if (reflect_hit.distance >= 0.f)
		hit.color = vector_add(hit.color,
				scalar_mul(hit.obj->reflect_ratio, reflect_hit.color));

	// diffuse
	for (int i = 0; i < this->scene->light_num; i++) {
		t_vector light_dir = vector_normalize(vector_sub(this->scene->lights[i]->pos, hit.point));
		float diffuse = vector_dot(light_dir, hit.normal);
		if (diffuse > 0) {
			hit.color = vector_add(hit.color, scalar_mul(diffuse, this->scene->lights[i]->color));
		}
	}

	// specular
	for (int i = 0; i < this->scene->light_num; i++) {
		t_vector light_dir = vector_normalize(vector_sub(this->scene->lights[i]->pos, hit.point));
		t_vector reflect_dir = vector_normalize(vector_sub(scalar_mul(2.f * vector_dot(light_dir, hit.normal), hit.normal), light_dir));
		float specular = powf(vector_dot(reflect_dir, vector_normalize(vector_sub(ray.origin, hit.point))), 100);
		if (specular > 0) {
			hit.color = vector_add(hit.color, scalar_mul(specular, this->scene->lights[i]->color));
		}
	}

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
	transform(&this->view_pos, &this->pos, &this->tr_view_mat);
	return ;
}

void	sphere_update_view_mat(t_object *this, t_matrix *tr_view_mat)
{
	this->tr_view_mat = *tr_view_mat;
	transform(&this->view_pos, &this->pos, tr_view_mat);
	return ;
}
