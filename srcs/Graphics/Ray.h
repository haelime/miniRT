/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:07:54 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/15 17:34:11 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "Vector.h"

typedef struct s_ray
{
	t_vector		origin;
	t_vector		dir;
}				t_ray;

t_ray	make_ray(t_vector origin, t_vector dir);

#endif
