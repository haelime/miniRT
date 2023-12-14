/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:25:03 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/14 15:05:15 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "Vector.h"
# include "Matrix.h"
# include "Scene.h"

typedef struct s_scene	t_scene;
typedef struct s_light
{
	t_vector	pos;
	t_vector	color;
	float		intensity;

	t_vector	view_pos;
	t_matrix	view_mat;
}				t_light;

void	light_update_view_mat(t_light *this, t_matrix *tr_view_mat);
void	add_light(t_scene *scene, t_light *light);

#endif // LIGHT_H
