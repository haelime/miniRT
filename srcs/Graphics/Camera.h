/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:27:40 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/09 16:20:20 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "Vector.h"
# include "Matrix.h"

typedef struct s_camera
{
	t_vector	pos;
	t_vector	norm_rotation;
	float		fov;
}				t_camera;

#endif // CAMERA_H
