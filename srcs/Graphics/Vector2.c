/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:45:06 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/10 20:51:25 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Vector.h"

int	vector_length(t_vector vector)
{
	return (sqrt(
			vector.x * vector.x
			+ vector.y * vector.y
			+ vector.z * vector.z));
}
