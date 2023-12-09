/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:08 by haeem             #+#    #+#             */
/*   Updated: 2023/12/09 16:15:33 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Phong.h"
#include "Vector.h"
#include "Object.h"
#include "Scene.h"

#include <stdio.h>

t_vector	get_phong_color(t_object *this, t_ray ray, t_hit hit, t_vector *out_specular)
{
	*out_specular = make_vector(0.f, 0.f, 0.f, 0.f);

	// ambient
	// hit.color = this->color;
	hit.color = vector_add(this->color,
			scalar_mul(this->scene->ambient_ratio, this->scene->ambient));

	// lighting
	for (int i = 0; i < this->scene->light_num; i++) {
		int is_shadow = 0;

		// check shadow
		for (int j = 0; j < this->scene->object_num; j++) {
			if (this->scene->objects[j] == this)
				continue ;
			t_ray shadow_ray;
			shadow_ray.origin = hit.point;
			shadow_ray.dir = vector_normalize(vector_sub(this->scene->lights[i]->view_pos, hit.point));
			//shadow_ray.origin = pos_add(shadow_ray.origin, scalar_mul(0.0001f, shadow_ray.dir));
			t_hit shadow_hit = this->scene->objects[j]->intersect(this->scene->objects[j], shadow_ray);
			if (shadow_hit.distance > 0 && shadow_hit.distance < vector_length(vector_sub(this->scene->lights[i]->view_pos, hit.point))
				&& shadow_hit.distance < vector_length(vector_sub(this->scene->lights[i]->view_pos, shadow_hit.point)))
				is_shadow = 1;

		}
		if (is_shadow)
			continue ;
		
		// diffuse
		t_vector light_dir = vector_normalize(vector_sub(this->scene->lights[i]->view_pos, hit.point));
		float diffuse = vector_dot(light_dir, hit.normal);
		if (diffuse > 0)
			hit.color = vector_add(hit.color, scalar_mul(diffuse, this->scene->lights[i]->color));
		hit.color = vector_clamp(hit.color, 0.f, 255.f);
		// specular
		t_vector reflect_dir = vector_normalize(vector_sub(scalar_mul(2.f * vector_dot(light_dir, hit.normal), hit.normal), light_dir));
		float specular_dot = vector_dot(reflect_dir, vector_normalize(vector_sub(ray.origin, hit.point)));
		// handle over 180 degree case
		if (specular_dot < 0)
			continue ;
		float specular = powf(specular_dot, 100);
			*out_specular = pos_add(*out_specular, scalar_mul(this->scene->lights[i]->intensity, scalar_mul(specular, this->scene->lights[i]->color)));
	}

	return (hit.color);
}
