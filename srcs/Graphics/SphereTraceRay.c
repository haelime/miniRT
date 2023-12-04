/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SphereTraceRay.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:43:42 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/04 19:40:48 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Sphere.h"
#include "Scene.h"

#include <stdio.h> // DEBUG

t_hit	sphere_trace_ray(t_object *this, t_ray ray, int recursion_num)
{
	t_hit		hit;
	t_hit		reflect_hit;
	t_vector	specular;

	hit.distance = -1.f;
	hit = sphere_intersect(this, ray);
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

t_hit	sphere_intersect(t_object *this, t_ray ray)
{
	t_hit		hit;
	float		b;
	float		c;
	float		nabla;
	float		dis2;

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
	dis2 = (-b / 2.f) - sqrtf(nabla);
	if ((hit.distance > dis2 && dis2 >= 0.f) || hit.distance < 0.f)
		hit.distance = dis2;
	hit.point = pos_add(ray.origin, scalar_mul(hit.distance, ray.dir));
	hit.normal = vector_normalize(vector_sub(hit.point, this->view_pos));
	hit.color = this->color;
	return (hit);
}

t_vector
	sphere_get_phong_color(t_object *this, t_ray ray, t_hit hit, t_vector *out_specular)
{
	*out_specular = make_vector(0.f, 0.f, 0.f, 0.f);

	// ambient
	hit.color = vector_add(this->color,
			scalar_mul(this->scene->ambient_ratio, this->scene->ambient));
	hit.color = vector_clamp(hit.color, 0, 255);

	// lighting
	for (int i = 0; i < this->scene->light_num; i++) {
		int is_shadow = 0;

		// check shadow
		for (int j = 0; j < this->scene->object_num; j++) {
			t_ray shadow_ray;
			shadow_ray.origin = hit.point;
			shadow_ray.origin = pos_add(shadow_ray.origin, scalar_mul(0.001, shadow_ray.dir));
			shadow_ray.dir = vector_normalize(vector_sub(this->scene->lights[i]->pos, hit.point));
			t_hit shadow_hit = this->scene->objects[j]->intersect(this->scene->objects[j], shadow_ray);
			// handle with [this_obj <-> light <-> shadow_obj] case
			if (shadow_hit.distance >= 0.f && shadow_hit.distance < vector_length(vector_sub(this->scene->lights[i]->pos, hit.point))) {
				is_shadow = 1;
				break ;
			}
		}
		if (is_shadow) {
			hit.color = make_vector(0,0,0,0);
			continue ;
		}
		
		// diffuse
		t_vector light_dir = vector_normalize(vector_sub(this->scene->lights[i]->pos, hit.point));
		float diffuse = vector_dot(light_dir, hit.normal);
		if (diffuse > 0)
			hit.color = vector_add(hit.color, scalar_mul(diffuse, this->scene->lights[i]->color));
		// specular
		t_vector reflect_dir = vector_normalize(vector_sub(scalar_mul(2.f * vector_dot(light_dir, hit.normal), hit.normal), light_dir));
		float specular_dot = vector_dot(reflect_dir, vector_normalize(vector_sub(ray.origin, hit.point)));
		// handle over 180 degree case
		if (specular_dot < 0)
			continue ;
		float specular = powf(specular_dot, 100);
		*out_specular = pos_add(*out_specular, scalar_mul(this->scene->lights[i]->intensity, scalar_mul(specular, this->scene->lights[i]->color)));
		vector_clamp(*out_specular, 0.f, 255.f);
	}

	return (hit.color);
}
