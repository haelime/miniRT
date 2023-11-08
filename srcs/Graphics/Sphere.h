/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:53:22 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 17:23:04 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "Object.h"
# include "Vector.h"
# include "Matrix.h"

typedef struct s_sphere
{
	t_object		object;
	double			radius;
}				t_sphere;

t_hit		sphere_get_hit(t_vector	*ray, t_vector	*origin);

void		sphere_transform(t_matrix *matrix);

#endif
