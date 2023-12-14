/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:08 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 17:55:21 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Phong.h"
#include "Vector.h"
#include "Object.h"
#include "Scene.h"
#include <stdbool.h>

#include <stdio.h>

void	add_diffuse_color(t_object *this, t_hit *hit, int i)
{
	const t_vector	light_dir = vector_normalize(
			vector_sub(this->scene->lights[i]->view_pos, hit->point));
	const float		diffuse = vector_dot(light_dir, hit->normal);

	if (diffuse > 0)
		hit->color = vector_add(
				hit->color, scalar_mul(diffuse, this->scene->lights[i]->color));
	hit->color = vector_clamp(hit->color, 0.f, 255.f);
}

bool	is_shadowed(t_object *this, t_hit *hit, int i)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	int		j;

	j = -1;
	while (++j < this->scene->object_num)
	{
		if (this->scene->objects[j] == this)
			continue ;
		shadow_ray.origin = hit->point;
		shadow_ray.dir = vector_normalize(
				vector_sub(this->scene->lights[i]->view_pos, hit->point));
		shadow_hit = this->scene->objects[j]->intersect(
				this->scene->objects[j], shadow_ray);
		if (shadow_hit.distance > 0 && shadow_hit.distance
			< vector_length(vector_sub(this->scene->lights[i]->view_pos,
					hit->point))
			&& shadow_hit.distance < vector_length(
				vector_sub(this->scene->lights[i]->view_pos, shadow_hit.point)))
			return (true);
	}
	return (false);
}

float	add_specular_color(t_object *this, t_ray ray, t_hit *hit, int i)
{
	t_vector	light_dir;
	t_vector	reflect_dir;
	float		specular_dot;

	light_dir = vector_normalize(vector_sub(
				this->scene->lights[i]->view_pos, hit->point));
	reflect_dir = vector_normalize(vector_sub(scalar_mul(
					2.f * vector_dot(light_dir, hit->normal), hit->normal),
				light_dir));
	specular_dot = vector_dot(reflect_dir, vector_normalize(
				vector_sub(ray.origin, hit->point)));
	return (specular_dot);
}

t_vector	get_phong_color(
		t_object *this, t_ray ray, t_hit hit, t_vector *out_specular)
{
	t_vector	light_dir;
	float		specular_dot;
	int			i;

	i = -1;
	*out_specular = make_vector(0.f, 0.f, 0.f, 0.f);
	hit.color = vector_add(this->color,
			scalar_mul(this->scene->ambient_ratio, this->scene->ambient));
	while (++i < this->scene->light_num)
	{
		if (is_shadowed(this, &hit, i))
			continue ;
		add_diffuse_color(this, &hit, i);
		light_dir = vector_normalize(vector_sub(
					this->scene->lights[i]->view_pos, hit.point));
		specular_dot = add_specular_color(this, ray, &hit, i);
		if (specular_dot < 0)
			continue ;
		*out_specular = pos_add(*out_specular, scalar_mul(this->scene->lights[i]
					->intensity, scalar_mul(powf(specular_dot, 100),
						this->scene->lights[i]->color)));
	}
	return (hit.color);
}
