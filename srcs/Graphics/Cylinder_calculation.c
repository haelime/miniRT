/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:44:56 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 17:53:23 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Cylinder.h"
#include "Vector.h"
#include "Object.h"
#include "Ray.h"

t_vector	calculate_oc(t_ray ray, const t_cylinder *cylinder)
{
	return (vector_sub(ray.origin, cylinder->object.view_pos));
}

double	calculate_a(t_ray ray, const t_cylinder *cylinder)
{
	return (vector_dot(ray.dir, ray.dir)
		- pow(vector_dot(ray.dir, cylinder->normal_view), 2));
}

double	calculate_b(t_ray ray, const t_cylinder *cylinder, t_vector oc)
{
	return (2.0 * (vector_dot(ray.dir, oc) - (vector_dot(
					ray.dir, cylinder->normal_view)
				* vector_dot(oc, cylinder->normal_view))));
}

double	calculate_c(t_vector oc, const t_cylinder *cylinder)
{
	return (vector_dot(oc, oc) - pow(vector_dot(
				oc, cylinder->normal_view), 2)
		- (cylinder->radius * cylinder->radius));
}

double	calculate_discriminant(t_ray ray, const t_cylinder *cylinder, double *t)
{
	const t_vector		oc = calculate_oc(ray, cylinder);
	const double		a = calculate_a(ray, cylinder);
	const double		b = calculate_b(ray, cylinder, oc);
	const double		c = calculate_c(oc, cylinder);
	const double		discriminant = b * b - 4 * a * c;

	*t = find_intersection(a, b, discriminant);
	return (discriminant);
}
