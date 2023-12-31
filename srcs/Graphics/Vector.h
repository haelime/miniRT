/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:24:03 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/03 18:58:54 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	__attribute__((aligned(16)))
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector;

t_vector	make_vector(float x, float y, float z, float w);
t_vector	make_unit_vector(t_vector vector);
t_vector	vector_add(t_vector a, t_vector b);
t_vector	scalar_mul(float scalar, t_vector vector);
t_vector	pos_sub(t_vector a, t_vector b);
t_vector	vector_sub(t_vector a, t_vector b);
t_vector	vector_mul(t_vector a, t_vector b);
t_vector	pos_add(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
float		vector_length(t_vector vector);
float		vector_dot(t_vector a, t_vector b);
t_vector	vector_normalize(t_vector x);
t_vector	vector_clamp(t_vector a, float min, float max);
t_vector	vector_mix(t_vector a, t_vector b, float min, float max);

#endif // VECTOR_H
