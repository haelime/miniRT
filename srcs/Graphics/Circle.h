/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Circle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:08:49 by haeem             #+#    #+#             */
/*   Updated: 2023/12/07 17:12:04 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCLE_H
# define CIRCLE_H

# include "Object.h"

typedef struct s_circle
{
	t_object	object;
	t_vector	v_world;
	t_vector	v_view;
	t_vector	normal_view;

	double		radius;
}t_circle;


void	circle_func_init(t_circle *this);
t_hit	circle_intersect(t_object *this, t_ray ray);
void	circle_init_world_coord(t_object *this);
void	circle_update_view_mat(t_object *this, t_matrix *tr_view_mat);

#endif