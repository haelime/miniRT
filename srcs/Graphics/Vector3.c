/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:45:06 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/03 20:33:40 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Matrix.h"

t_vector	pos_add(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	ret.w = 1.f;
	return (ret);
}

t_vector	vector_clamp(t_vector a, float min, float max)
{
	t_vector	ret;

	ret = a;
	if (a.x < min)
		ret.x = min;
	else if (a.x > max)
		ret.x = max;
	if (a.y < min)
		ret.y = min;
	else if (a.y > max)
		ret.y = max;
	if (a.z < min)
		ret.z = min;
	else if (a.z > max)
		ret.z = max;
	if (a.w < min)
		ret.w = min;
	else if (a.w > max)
		ret.w = max;
	return (ret);
}

t_vector	vector_mix(t_vector a, t_vector b, float min, float max)
{
	t_vector	ret;
	float		max_rgb;
	float		max_rgb_clamp;

	if (a.x == 255 && a.y == 255 && a.z == 255)
		max_rgb = 0;
	ret.x = (a.x * (b.x / 255));
	ret.y = (a.y * (b.y / 255));
	ret.z = (a.z * (b.z / 255));
	ret.w = 0;
	return (ret);
}
t_vector	vector_mul(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	ret.w = 0;

	return ret;
}