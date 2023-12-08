/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:59:28 by haeem             #+#    #+#             */
/*   Updated: 2023/12/08 18:01:15 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include "Light.h"
#include "Object.h"
#include "Matrix.h"

void	light_update_view_mat(t_light *this, t_matrix *tr_view_mat)
{
	transform(&this->view_pos, &this->pos, tr_view_mat);
	return ;
}
