/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:07:54 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/06 19:43:43 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "Vector.h"
# include "Object.h"
# include "Scene.h"

typedef struct s_hit	t_hit;
typedef struct s_object	t_object;
typedef struct s_ray
{
	t_vector		origin;
	t_vector		dir;
}				t_ray;

t_ray	make_ray(t_vector origin, t_vector dir);
t_hit	trace_ray(t_object *this, t_ray ray, int recursion_num);

#endif
