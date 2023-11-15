/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:33:57 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/15 17:34:07 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ray.h"

t_ray	make_ray(t_vector origin, t_vector dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.dir = dir;
	return (ray);
}
