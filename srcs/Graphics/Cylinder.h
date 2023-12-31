/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:34:51 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 17:53:53 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "Object.h"
# include "Vector.h"
# include "Matrix.h"

// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// identifier: cy
// x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// 3d normalized vector of axis of cylinder.
// In range [-1,1] for each x,y,z axis:
// 0,0.0,1.0
// the cylinder diameter: 14.2
// the cylinder height: 21.42
// R,G,B colors in range [0,255]: 10, 0, 255
typedef struct s_cylinder
{
	t_object		object;
	double			radius;
	double			diameter;
	double			height;

	t_vector		v_world;
	t_vector		v_view;
	t_vector		normal;
	t_vector		normal_view;
}				t_cylinder;

void		cylinder_func_init(t_cylinder *this);

void		cylinder_init_world_coord(t_object *this);
void		cylinder_update_view_mat(t_object *this, t_matrix *tr_view_mat);
t_hit		cylinder_intersect(t_object *this, t_ray ray);

t_vector	calculate_oc(t_ray ray, const t_cylinder *cylinder);
double		calculate_a(t_ray ray, const t_cylinder *cylinder);
double		calculate_b(t_ray ray, const t_cylinder *cylinder, t_vector oc);
double		calculate_c(t_vector oc, const t_cylinder *cylinder);
double		calculate_discriminant(t_ray ray,
				const t_cylinder *cylinder, double *t);
double		find_intersection(double a, double b, double discriminant);

#endif
