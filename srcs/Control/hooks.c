/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:00:13 by haeem             #+#    #+#             */
/*   Updated: 2023/12/08 19:53:19 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "macros.h"
#include "mlx.h"
#include "ControlBlock.h"

void	keypressed_debug(int keycode, void *param)
{
	t_control_block	*cb;

	cb = (t_control_block *)param;
	if (keycode == KEY_R)
	{
		cb->is_debug ^= true;
	}
	else
		return ;
	render_scene(&cb->scene, &cb->img, (int)cb->is_debug);
	mlx_put_image_to_window(cb->mlx.mlx, cb->mlx.win, cb->img.ptr, 0, 0);
}

void	keypressed_rotation(int keycode, void *param)
{
	t_control_block	*cb;

	cb = (t_control_block *)param;
	if (keycode == KEY_UP)
		cb->scene.camera->norm_rotation.x -= 0.1;
	else if (keycode == KEY_DOWN)
		cb->scene.camera->norm_rotation.x += 0.1;
	else if (keycode == KEY_LEFT)
		cb->scene.camera->norm_rotation.y -= 0.1;
	else if (keycode == KEY_RIGHT)
		cb->scene.camera->norm_rotation.y += 0.1;
	else if (keycode == KEY_Q)
		cb->scene.camera->norm_rotation.z -= 0.1;
	else if (keycode == KEY_E)
		cb->scene.camera->norm_rotation.z += 0.1;
	else
	{
		keypressed_debug(keycode, param);
		return ;
	}
	render_scene(&cb->scene, &cb->img, (int)cb->is_debug);
	mlx_put_image_to_window(cb->mlx.mlx, cb->mlx.win, cb->img.ptr, 0, 0);
}

void	keypressed(int keycode, void *param)
{
	t_control_block	*cb;

	cb = (t_control_block *)param;
	if (keycode == KEY_ESCAPE)
		exit(0);
	else if (keycode == KEY_W)
		cb->scene.camera->pos.z += 10;
	else if (keycode == KEY_S)
		cb->scene.camera->pos.z -= 10;
	else if (keycode == KEY_A)
		cb->scene.camera->pos.x -= 10;
	else if (keycode == KEY_D)
		cb->scene.camera->pos.x += 10;
	else if (keycode == KEY_SPACEBAR)
		cb->scene.camera->pos.y += 10;
	else if (keycode == KEY_SHIFT_LEFT)
		cb->scene.camera->pos.y -= 10;
	else
	{
		keypressed_rotation(keycode, param);
		return ;
	}
	render_scene(&cb->scene, &cb->img, (int)cb->is_debug);
	mlx_put_image_to_window(cb->mlx.mlx, cb->mlx.win, cb->img.ptr, 0, 0);
}

void	hooks(t_control_block *cb)
{
	// cb->scene.camera->pos;
	mlx_hook(cb->mlx.win, KEYPRESS, 1L << 0, (void *)keypressed, cb);
	mlx_hook(cb->mlx.win, 17, 0, (void *)exit, (0));
}
