/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:39:21 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/10 15:21:43 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.h"
#include "libft.h"

void	add_object(t_scene *scene, t_object *object)
{
	t_object	**new_objects;

	if (scene->object_num == scene->object_capacity)
	{
		if (scene->object_capacity == 0)
			scene->object_capacity = 1;
		else
			scene->object_capacity *= 2;
		new_objects
			= (t_object **)malloc(sizeof(t_object*) * scene->object_capacity);
		ft_memcpy(
			new_objects, scene->objects, sizeof(t_object*) * scene->object_num);
		free(scene->objects);
		scene->objects = new_objects;
	}
	scene->objects[scene->object_num] = object;
	scene->object_num++;
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
