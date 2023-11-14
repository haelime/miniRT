/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:39:21 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 22:23:13 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Scene.h"
#include "libft.h"
#include "Object.h"
#include "Vector.h"
#include "Matrix.h"

#include <stdio.h> //DEBUG //TODO: remove

void	render_scene(t_scene *scene, t_img *img, int is_debug_mode)
{
	int			x;
	int			y;
	t_vector	origin;
	t_vector	ray;
	t_hit		hit;

	y = -1;
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			origin = make_vector(0.f, 0.f, 0.f, 0.f);
			ray = make_vector(
				(float)x - IMG_WIDTH/ 2.f,
				(float)y - IMG_HEIGHT / 2.f,
				(float)IMG_WIDTH / (2.f * tanf(scene->camera->fov / 2.f)),
				1.f);
			ray = vector_normalize(ray);
			for (int i = 0; i < scene->object_num; i++)
			{
				t_matrix tmp;
				make_diagonal_matrix(&tmp, make_vector(1.f, 1.f, 1.f, 1.f));
				hit = scene->objects[i]->intersect(
					scene->objects[i], origin, ray, &tmp);
				if (hit.distance >= 0.f)
					break ;
			}
			//printf("distance = %f\n", hit.distance);
			if (hit.distance <= 0.f) {
				img->data[x + y * IMG_WIDTH] = 120;
			}
			else
			{
				img->data[x + y * IMG_WIDTH] = (int)hit.color.x | (int)hit.color.y << 8 | (int)hit.color.z << 16 | 0xFF << 24; 
			}
		}
	}
	img->data[100] = 0xFFFFFFFF;
	img->data[101] = 0xFFFFFFFF;
	img->data[102] = 0xFFFFFFFF;
	printf("end\n");
}

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
