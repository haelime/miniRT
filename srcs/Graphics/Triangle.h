/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:53:22 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/28 16:21:38 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "Object.h"
# include "Vector.h"
# include "Matrix.h"

typedef struct s_triangle
{
	t_object		object;
	t_vector		normal;
	t_vector		v[3];
	t_vector		v_world[3];
	t_vector		v_view[3];
}				t_triangle;

void	triangle_func_init(t_triangle *this);
t_hit	triangle_intersect(t_object *this, t_ray ray);
void	triangle_init_world_coord();
void	triangle_update_view_mat();
t_hit	triangle_trace_ray(t_object *this, t_ray ray, int recursion_num);

#endif // TRIANGLE_H