/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:53:22 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 16:42:10 by hyunjunk         ###   ########.fr       */
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

t_hit		get_hit(t_vector	*ray, t_vector	*origin);

void		transform(t_matrix *matrix);

#endif
