/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:19:40 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 17:54:35 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "Vector.h"
# include "Matrix.h"

typedef struct s_hit	t_hit;

typedef struct s_object {
	t_vector	pos;
	t_vector	normal;
	t_vector	color;
	float		reachable_max_radius;
	t_hit		((*get_hit)(t_vector	*ray, t_vector	*origin));
	void		((*transform)(t_matrix *matrix));
}				t_object;

typedef struct s_hit {
	t_vector	point;
	t_vector	color;
	float		distance;
}				t_hit;

#endif // OBJECT_H
