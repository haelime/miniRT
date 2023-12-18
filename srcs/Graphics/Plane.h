/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:02:52 by haeem             #+#    #+#             */
/*   Updated: 2023/12/18 16:31:25 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "Object.h"

typedef struct s_plane
{
	t_object	object;
	t_vector	v_world;
	t_vector	v_view;
	t_vector	normal;
	t_vector	normal_view;
}t_plane;

void	plane_func_init(t_plane *this);
t_hit	plane_intersect(t_object *this, t_ray ray);
void	plane_init_world_coord(t_object *this);
void	plane_update_view_mat(t_object *this, t_matrix *tr_view_mat);

#endif