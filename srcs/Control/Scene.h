/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:24:29 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/10 15:21:45 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "Object.h"
# include "Light.h"
# include "Camera.h"

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
