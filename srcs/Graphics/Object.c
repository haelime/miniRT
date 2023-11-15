/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:00:40 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/15 17:36:48 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Object.h"

t_vector	make_reflect_ray(t_hit hit, t_vector ray)
{
	t_vector	reflect_ray;

	reflect_ray = vector_normalize(
			vector_sub(ray,
				scalar_mul(2.f * vector_dot(ray, hit.normal), hit.normal)));
	return (reflect_ray);
}
