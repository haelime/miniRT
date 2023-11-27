/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:39:21 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/27 17:57:33 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "Scene.h"
#include "libft.h"
#include "Object.h"
#include "Vector.h"
#include "Matrix.h"

#include <stdio.h> //DEBUG //TODO: remove

t_hit	compute_reflect_recursive(
		t_scene *scene, t_hit hit, t_ray hit_ray, int recursion_num)
{
	t_hit		reflect_hit;
	t_hit		tmp;
	t_ray		reflect;
	int			i;

	reflect_hit.distance = -1.f;
	if (recursion_num <= 0)
		return (reflect_hit);
	reflect.dir = vector_normalize(vector_sub(
				hit_ray.dir, scalar_mul(2.f
					* vector_dot(hit_ray.dir, hit.normal), hit.normal)));
	reflect.origin = pos_add(hit_ray.origin, scalar_mul(0.01, reflect.dir));
	i = -1;
	while (++i < scene->object_num)
	{
		tmp = scene->objects[i]->trace_ray(
				scene->objects[i], reflect, recursion_num - 1);
		if (tmp.distance >= 0.f && (reflect_hit.distance < 0.f
				|| tmp.distance < reflect_hit.distance))
			reflect_hit = tmp;
	}
	return (reflect_hit);
}

int		clamp255(int x) {
	if (x > 255)
		return 255;
	return x;
}

void	render_scene(t_scene *scene, t_img *img, int is_debug_mode)
{
	int			x;
	int			y;
	t_vector	origin;
	t_vector	ray;
	t_hit		hit;

	transform_scene_camera_coord(scene);

	y = -1;
	while (++y < IMG_HEIGHT)
	{
		printf("%d\n", y);
		x = -1;
		while (++x < IMG_WIDTH)
		{
			if (y == 0)
				printf("%d\n", x);

			// origin on screen
			origin = make_vector(
				((float)x / (float)IMG_WIDTH * 2.f - 1.f) * ((float)IMG_WIDTH / (float)IMG_HEIGHT),
				-((float)y / (float)IMG_HEIGHT * 2.f - 1.f),
				1.f/tanf(scene->camera->fov / 2), 1.f);
			// ray direction
			ray = make_vector(
				origin.x, origin.y, 1.f, 0.f);
			ray = vector_normalize(ray);

			

			for (int i = 0; i < scene->object_num; i++)
			{
				//DEBUG
				t_matrix tmp_tr_camera;
				make_diagonal_matrix(&tmp_tr_camera, make_vector(1.f, 1.f, 1.f, 1.f));
				for (int j = 0; j < scene->object_num; j++) {
					//scene->objects[j]->update_view_mat(scene->objects[j], &tmp_tr_camera);
					scene->objects[j]->reflect_ratio = 0.5f;
				}

				// TODO : rm false when done
				if (false && !is_debug_mode) {
					hit = scene->objects[i]->trace_ray(
						scene->objects[i], make_ray(origin, ray), 2);
				}
				else {
					hit = scene->objects[i]->intersect(
						scene->objects[i], make_ray(origin, ray));
					hit.color = hit.obj->color;
				}
				if (hit.distance >= 0.f)
					break;
			}

			//printf("distance = %f\n", hit.distance);
			if (hit.distance <= 0.f) {
				img->data[x + y * IMG_WIDTH] = 255;
			}
			else
			{
				img->data[x + y * IMG_WIDTH] = (clamp255((int)hit.color.x) | clamp255((int)hit.color.y) << 8 | clamp255((int)hit.color.z) << 16) & 0x00FFFFFF;
			}
		}
	}
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
