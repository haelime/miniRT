/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:33:57 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/09 16:17:02 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Ray.h"
#include "Phong.h"

t_ray	make_ray(t_vector origin, t_vector dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = dir;
	return (ray);
}

t_hit	trace_ray(t_object *this, t_ray ray, int recursion_num)
{
	t_hit		hit;
	t_hit		reflect_hit;
	t_vector	specular;

	hit.distance = -1.f;
	hit = this->intersect(this, ray);
	if (hit.distance < 0.f)
		return (hit);
	hit.color = scalar_mul(1.f - this->reflect_ratio, vector_clamp(
				get_phong_color(this, ray, hit, &specular), 0.f, 255.f));
	hit.color = vector_add(hit.color, specular);
	hit.color = vector_clamp(hit.color, 0.f, 255.f);
	if (recursion_num <= 0)
		return (hit);
	reflect_hit
		= compute_reflect_recursive(this->scene, hit, ray, recursion_num);
	if (reflect_hit.distance <= 0)
		return (hit);
	reflect_hit.color = vector_clamp(reflect_hit.color, 0.f, 255.f);
	hit.color = vector_add(hit.color,
			scalar_mul(
				this->reflect_ratio,
				reflect_hit.color));
	hit.color = vector_clamp(hit.color, 0.f, 255.f);
	return (hit);
}
