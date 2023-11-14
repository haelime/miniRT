/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:53:22 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 21:40:17 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "Object.h"
# include "Vector.h"
# include "Matrix.h"

typedef struct s_sphere
{
	t_object		object;
	double			radius;
}				t_sphere;

void	sphere_func_init(t_sphere *this);

t_hit	sphere_intersect(t_object *this,
			t_vector	origin, t_vector	ray, t_matrix *tr_view_mat);
void	sphere_update_rotation(t_object *this, t_vector rot);
void	sphere_update_pos(t_object *this, t_vector pos);

#endif
