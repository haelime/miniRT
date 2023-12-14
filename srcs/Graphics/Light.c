/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:59:28 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 15:11:49 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Vector.h"
#include "Light.h"
#include "Object.h"
#include "Matrix.h"
#include "libft.h"

void	light_update_view_mat(t_light *this, t_matrix *tr_view_mat)
{
	transform(&this->view_pos, &this->pos, tr_view_mat);
	return ;
}

void	add_light(t_scene *scene, t_light *light)
{
	t_light		**new_lights;

	if (scene->light_num == scene->light_capacity)
	{
		if (scene->light_capacity == 0)
			scene->light_capacity = 1;
		else
			scene->light_capacity *= 2;
		new_lights
			= (t_light **)malloc(sizeof(t_light*) * scene->light_capacity);
		ft_memcpy(
			new_lights, scene->lights, sizeof(t_light*) * scene->light_num);
		free(scene->lights);
		scene->lights = new_lights;
	}
	scene->lights[scene->light_num] = light;
	scene->light_num++;
}
