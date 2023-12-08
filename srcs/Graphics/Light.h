/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:25:03 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/08 18:01:55 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "Vector.h"
# include "Matrix.h"

typedef struct s_light
{
	t_vector	pos;
	t_vector	color;
	float		intensity;

	t_vector	view_pos;
	t_matrix	view_mat;
}				t_light;

void	light_update_view_mat(t_light *this, t_matrix *tr_view_mat);

#endif // LIGHT_H
