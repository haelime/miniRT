/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:00:13 by haeem             #+#    #+#             */
/*   Updated: 2023/11/14 16:47:17 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "../../includes/macros.h"
#include <stdlib.h>

int exit_rt(void *param)
{
	exit(0);
	return (0);
}

void keypressed3(int keycode, void *param)
{
	if (keycode == KEY_P)
	{
	}
	if (keycode == KEY_O)
	{
	}
}

void keypressed2(int keycode, void *param)
{
	if (keycode == KEY_E)
		;
	if (keycode == KEY_R)
		;
	if (keycode == KEY_F)
		;
	if (keycode == KEY_T)
		;
	if (keycode == KEY_G)
		;
	if (keycode == KEY_Z)
		;
	if (keycode == KEY_X)
		;
}

void keypressed(int keycode, void *param)
{
	if (keycode == KEY_ESCAPE)
		exit_rt(param);
	// if (keycode == KEY_W)
	// if (keycode == KEY_S)
	// if (keycode == KEY_A)
	// if (keycode == KEY_D)
	// if (keycode == KEY_Q)

	// keypressed2(keycode, param);
	// keypressed3(keycode, param);
	// make_image(((t_map *)param)->img, (t_map *)param);
}

void hooks(void *win, t_img *img, t_map *map)
{
	mlx_hook(win, KEYPRESS, 1L << 0, (void *)keypressed, map);
	mlx_hook(win, 17, 0, (void *)exit, (0));
}
