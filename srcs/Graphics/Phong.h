/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phong.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:16:16 by haeem             #+#    #+#             */
/*   Updated: 2023/12/06 19:36:59 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_H
# define PHONG_H

# include "Vector.h"
# include "Object.h"
# include "Scene.h"

t_vector	get_phong_color(t_object *this, t_ray ray, t_hit hit,
				t_vector *out_specular);

#endif