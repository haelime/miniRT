/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:45:06 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 21:52:44 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Matrix.h"

float	vector_length(t_vector vector)
{
	return (sqrtf(
			vector.x * vector.x
			+ vector.y * vector.y
			+ vector.z * vector.z));
}

float	vector_dot(t_vector a, t_vector b)
{
	t_sse	x;
	float	ret;

	x.xmm0 = _mm_load_ps(&a.x);
	x.xmm1 = _mm_load_ps(&b.x);
	x.xmm0 = _mm_dp_ps(x.xmm0, x.xmm1, 0xff);
	_mm_store_ss(&ret, x.xmm0);
	return (ret);
}

t_vector	vector_normalize(t_vector x)
{
	t_vector		ret;
	const float		length = sqrtf(
			x.x * x.x
			+ x.y * x.y
			+ x.z * x.z);

	ret.x = x.x / length;
	ret.y = x.y / length;
	ret.z = x.z / length;
	ret.w = 0.f;
	return (ret);
}

t_vector	vector_add(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	ret.w = 0.f;
	return (ret);
}

t_vector	scalar_mul(float scalar, t_vector vector)
{
	t_vector	ret;

	ret.x = scalar * vector.x;
	ret.y = scalar * vector.y;
	ret.z = scalar * vector.z;
	ret.w = vector.w;
	return (ret);
}
