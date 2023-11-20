/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:53:22 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/20 19:46:14 by hyunjunk         ###   ########.fr       */
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

void		sphere_func_init(t_sphere *this);

t_hit		sphere_trace_ray(t_object *this, t_ray ray, int recursion_num);
t_hit		sphere_intersect(t_object *this, t_ray ray);
t_vector	sphere_get_phong_color(
				t_object *this, t_ray ray, t_hit hit, t_vector *out_specular);
void		sphere_init_world_coord(t_object *this);
void		sphere_update_view_mat(t_object *this, t_matrix *tr_view_mat);

#endif
