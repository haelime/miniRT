/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:39:21 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/20 14:32:56 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "Scene.h"
#include "libft.h"
#include "Object.h"
#include "Vector.h"
#include "Matrix.h"

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
	reflect.origin = pos_add(hit_ray.origin, scalar_mul(0.0001, reflect.dir));
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

t_vector	make_origin_vector(int x, int y, t_scene *scene)
{
	t_vector	origin;

	origin = make_vector(((float)x / (float)IMG_WIDTH * 2.f - 1.f)
			* ((float)IMG_WIDTH / (float)IMG_HEIGHT),
			-((float)y / (float)IMG_HEIGHT * 2.f - 1.f),
			1.f / tanf(scene->camera->fov * (M_PI / 180) / 2), 1.f);
	return (origin);
}

t_hit	get_pixel_color(int x, int y, t_scene *scene, int is_debug_mode)
{
	t_vector	origin;
	t_vector	ray;
	t_hit		hit;
	t_hit		tmp;
	int			i;

	origin = make_origin_vector(x, y, scene);
	ray = make_vector(origin.x, origin.y, origin.z, 0.f);
	ray = vector_normalize(ray);
	hit.distance = -1;
	i = -1;
	while (++i < scene->object_num)
	{
		if (is_debug_mode)
			tmp = scene->objects[i]->trace_ray(
					scene->objects[i], make_ray(origin, ray), 2);
		else
			tmp = scene->objects[i]->intersect(
					scene->objects[i], make_ray(origin, ray));
		if (tmp.distance >= 0.f && (hit.distance < 0.f
				|| tmp.distance < hit.distance))
			hit = tmp;
	}
	return (hit);
}

void	render_scene(t_scene *scene, t_img *img, int is_debug_mode)
{
	int			x;
	int			y;
	t_hit		hit;

	transform_scene_camera_coord(scene);
	y = -1;
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			hit = get_pixel_color(x, y, scene, is_debug_mode);
			if (hit.distance <= 0.f)
				img->data[x + y * IMG_WIDTH] = 0;
			else
				img->data[x + y * IMG_WIDTH] = (clamp255((int)hit.color.z)
						| clamp255((int)hit.color.y) << 8
						| clamp255((int)hit.color.x) << 16) & 0xFFFFFF;
		}
	}
	printf("done\n");
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
