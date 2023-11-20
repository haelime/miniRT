/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:19:40 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/20 15:24:21 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "Vector.h"
# include "Matrix.h"
# include "Ray.h"

typedef struct s_hit	t_hit;
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
	void		((*update_rotation)(t_object *this, t_vector rot));
	void		((*update_pos)(t_object *this, t_vector pos));
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
