/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:53:22 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 21:55:00 by hyunjunk         ###   ########.fr       */
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
	t_vector		v_trans[3];
}				t_triangle;

void	triangle_func_init(t_triangle *this);

t_hit	triangle_intersect(t_object *this,
			t_vector	origin, t_vector ray, t_matrix *tr_view_mat);
void	triangle_update_rotation(t_object *this, t_vector rot);
void	triangle_update_pos(t_object *this, t_vector pos);

#endif // TRIANGLE_H