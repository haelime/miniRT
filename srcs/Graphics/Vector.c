/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:45:06 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/30 18:07:52 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Vector.h"

t_vector	make_vector(float x, float y, float z, float w)
{
	t_vector	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = w;
	return (ret);
}

t_vector	make_unit_vector(t_vector vector)
{
	t_vector	ret;
	float		length;

	length = sqrtf(
			vector.x * vector.x
			+ vector.y * vector.y
			+ vector.z * vector.z);
	ret.x = vector.x / length;
	ret.y = vector.y / length;
	ret.z = vector.z / length;
	ret.w = 0.f;
	return (ret);
}

t_vector	vector_sub(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	ret.w = 0.f;
	return (ret);
}

t_vector	pos_sub(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	ret.w = 1.f;
	return (ret);
}

t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	ret.w = 0.0;
	return (ret);
}
