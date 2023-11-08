/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:39:21 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 17:42:39 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scene.h"
#include "libft.h"

void	add_object(t_scene *scene, t_object *object)
{
	t_object	*new_objects;

	if (scene->object_num == scene->object_capacity)
	{
		scene->object_capacity *= 2;
		new_objects
			= (t_object *)malloc(sizeof(t_object) * scene->object_capacity);
		ft_memcpy(
			new_objects, scene->objects, sizeof(t_object) * scene->object_num);
		free(scene->objects);
		scene->objects = new_objects;
	}
	scene->objects[scene->object_num] = *object;
	scene->object_num++;
}
