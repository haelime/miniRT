/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:53:22 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 18:22:58 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "Object.h"
# include "Vector.h"
# include "Matrix.h"

typedef struct s_triangle
{
	t_object		object;
	t_vector		normal;
	t_vector		v[3];
}				t_triangle;

t_hit		triangle_get_hit(t_vector	*ray, t_vector	*origin);

void		triangle_transform(t_matrix *matrix);

#endif // TRIANGLE_H