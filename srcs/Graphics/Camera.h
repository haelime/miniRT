/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:27:40 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 16:46:48 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "Vector.h"
# include "Matrix.h"

typedef struct s_camera
{
	t_vector	pos;
	t_vector	normal;
	float		fov;
}				t_camera;

#endif // CAMERA_H