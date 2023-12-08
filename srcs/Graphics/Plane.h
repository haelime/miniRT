/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:02:52 by haeem             #+#    #+#             */
/*   Updated: 2023/12/08 18:10:18 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

// 평면
// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// 구별자 : pl
// x,y,z 좌표 : 0.0, 0.0, -10.0
// 정규화된 삼차원 방향 벡터. 각 x, y, z 축 마다 [-1, 1] 의 범위를 가짐 : 0.0, 0.0, 1.0
// R,G,B 색 범위 [0, 255] : 0, 0, 255 
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