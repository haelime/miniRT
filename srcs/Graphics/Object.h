/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:19:40 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/06 19:44:54 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "Vector.h"
# include "Matrix.h"
# include "Ray.h"

# define EPSILON (1.E-8f)
# define PI (3.14159265358979323f)

typedef struct s_hit	t_hit;
typedef struct s_ray	t_ray;
typedef struct s_scene	t_scene;
typedef struct s_object	t_object;

typedef struct s_object
{
	t_scene		*scene;
	t_vector	norm_rotation;
	t_vector	pos;
	t_vector	view_pos;
	t_vector	color;
	float		reflect_ratio;
	float		reachable_max_radius;
	t_hit		((*trace_ray)(t_object * this, t_ray ray, int recursion_num));
	t_hit		((*intersect)(t_object * this, t_ray ray));
	void		((*init_world_coord)(t_object *this));
	void		((*update_view_mat)(t_object *this, t_matrix *tr_view_mat));
	t_matrix	tr_rot_mat;
	t_matrix	tr_pos_mat;
	t_matrix	tr_view_mat;
}	t_object;

typedef struct s_hit {
	t_vector	point;
	t_vector	color;
	t_vector	normal;
	float		distance;
	t_object	*obj;
}				t_hit;

t_vector	make_reflect_ray(t_hit hit, t_vector ray);

#endif // OBJECT_H
