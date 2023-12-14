/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:33:43 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 17:52:32 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Cylinder.h"
#include "Scene.h"
#include "Object.h"
#include "Ray.h"

// Function to swap two values
void	swap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Function to find the valid intersection point
double	find_intersection(double a, double b, double discriminant)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > t2)
	{
		swap(&t1, &t2);
	}
	if (t2 < 0)
		return (-1.0);
	if (t1 > 0)
		return (t1);
	return (t2);
}

// Function to check if the intersection point is within the valid range
int	isvalid_intersection(double max, t_vector point, t_vector v_view)
{
	t_vector	len;

	len = vector_sub(point, v_view);
	if (vector_length(len) > max)
		return (0);
	else
		return (1);
}

// Function to calculate and return the hit information
t_hit	calculate_hit(t_object *this, double t,
				t_ray ray, const t_cylinder *cylinder)
{
	t_hit		hit;
	t_vector	normal;

	hit.distance = t;
	hit.obj = this;
	hit.point = vector_add(ray.origin, scalar_mul(t, ray.dir));
	normal = vector_sub(hit.point, cylinder->object.view_pos);
	normal = vector_sub(normal, scalar_mul(vector_dot(
					ray.dir, cylinder->normal_view), cylinder->normal_view));
	hit.normal = vector_normalize(normal);
	hit.color = this->color;
	return (hit);
}

t_hit	cylinder_intersect(t_object *this, t_ray ray)
{
	const t_cylinder	*cylinder = (t_cylinder *)this;
	double				t;
	const double		discriminant
		= calculate_discriminant(ray, cylinder, &t);
	t_hit				hit;

	hit.distance = -1.0;
	hit.obj = this;
	if (discriminant < 0)
		return (hit);
	if (!isvalid_intersection(sqrt(pow(cylinder->height / 2, 2)
				+ pow(cylinder->radius, 2)),
			vector_add(ray.origin, scalar_mul(t, ray.dir)),
			cylinder->object.view_pos))
		return (hit);
	return (calculate_hit(this, t, ray, cylinder));
}
