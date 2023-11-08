/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:54 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 17:59:01 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.h"

float	ft_max3f(float a, float b, float c)
{
	float	max;

	max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return (max);
}
