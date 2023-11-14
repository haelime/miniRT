/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:19:40 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 21:53:52 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "Vector.h"
# include "Matrix.h"
# include "Scene.h"

typedef struct s_hit	t_hit;
typedef struct s_scene	t_scene;
typedef struct s_object	t_object;

typedef struct s_object
{
	t_scene		*scene;
	t_vector	norm_rotation;
	t_vector	pos;
	t_vector	color;
	float		reachable_max_radius;
	t_hit		((*intersect)(
			t_object * this,
			t_vector origin, t_vector ray, t_matrix * tr_view_mat));
	void		((*update_rotation)(t_object *this, t_vector rot));
	void		((*update_pos)(t_object *this, t_vector pos));
	t_matrix	tr_rot_mat;
	t_matrix	tr_pos_mat;
}	t_object;

typedef struct s_hit {
	t_vector	point;
	t_vector	color;
	t_vector	normal;
	float		distance;
}				t_hit;

#endif // OBJECT_H
