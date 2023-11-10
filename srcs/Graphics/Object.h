/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:19:40 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/10 21:02:07 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "Vector.h"
# include "Matrix.h"
# include "Scene.h"

typedef struct s_hit	t_hit;

typedef struct s_object {
	t_scene		*scene;
	t_vector	pos;
	t_vector	norm_rotation;
	t_vector	color;
	float		reachable_max_radius;
	t_hit		((*get_hit)(t_vector	*ray, t_vector	*origin));
	void		((*transform_to_world)(t_matrix *matrix));
	void		((*transform_to_view)(t_matrix *matrix)); // TODO
}				t_object;

typedef struct s_hit {
	t_vector	point;
	t_vector	color;
	float		distance;
}				t_hit;

#endif // OBJECT_H
