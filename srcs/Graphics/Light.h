/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:25:03 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/06 19:26:57 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "Vector.h"

typedef struct s_light
{
	t_vector	center;
	t_vector	color;
	float		intensity;
}				t_light;

#endif // LIGHT_H
