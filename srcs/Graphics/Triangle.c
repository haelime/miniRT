/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:44:39 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 21:55:09 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Triangle.h"

void	triangle_func_init(t_triangle *this)
{
	this->object.intersect = triangle_intersect;
	this->object.update_rotation = triangle_update_rotation;
	this->object.update_pos = triangle_update_pos;
}

t_hit	triangle_intersect(t_object *this,
			t_vector	origin, t_vector ray, t_matrix *tr_view_mat)
{
	t_hit	hit;

	return (hit);
}

void	triangle_update_rotation(t_object *this, t_vector rot)
{
	return ;
}

void	triangle_update_pos(t_object *this, t_vector pos)
{
	return ;
}
