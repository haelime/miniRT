/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:24:29 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/14 18:42:50 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mlx.h"
# include "Image.h"
# include "Light.h"
# include "Camera.h"

typedef struct s_object t_object;
typedef struct s_scene
{
	t_object	**objects;
	int			object_num;
	int			object_capacity;

	t_light		**lights;
	int			light_num;
	int			light_capacity;

	t_vector	ambient;
	float		ambient_ratio;

	t_camera	*camera;
	t_vector	resolution;
}				t_scene;

void	add_object(t_scene *scene, t_object *object);
void	add_light(t_scene *scene, t_light *light);

#endif // SCENE_H
