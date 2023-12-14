/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:24:29 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/14 15:11:26 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mlx.h"
# include "Image.h"
# include "Light.h"
# include "Camera.h"
# include "Object.h"
# include "Ray.h"

typedef struct s_control_block	t_control_block;
typedef struct s_hit			t_hit;
typedef struct s_ray			t_ray;
typedef struct s_scene			t_scene;
typedef struct s_object			t_object;
typedef struct s_light			t_light;

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

// Should be called after all objects' transform matrices are updated
void		render_scene(t_scene *scene, t_img *img, int is_debug_mode);
void		init_render_scene(t_scene *scene);
void		transform_scene_camera_coord(t_scene *scene);
t_hit		compute_reflect_recursive(
				t_scene *scene, t_hit hit, t_ray hit_ray, int recursion_num);

void		add_object(t_scene *scene, t_object *object);
void		add_light(t_scene *scene, t_light *light);

t_matrix	make_trans_mat(t_vector pos);
t_matrix	make_tr_rot_x_mat(float angle);
t_matrix	make_tr_rot_y_mat(float angle);
t_matrix	make_tr_rot_z_mat(float angle);
t_matrix	make_tr_view_mat(t_camera *camera);
void		transform_scene_camera_coord(t_scene *scene);
int			clamp255(int x);

#endif // SCENE_H
