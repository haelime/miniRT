/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:24:29 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/06 19:36:11 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "Object.h"
# include "Light.h"
# include "Camera.h"

typedef struct s_scene
{
	t_object	*objects;
	t_vector	ambient;
	t_light		*lights;
	t_camera	*camera;
}				t_scene;

#endif // SCENE_H
