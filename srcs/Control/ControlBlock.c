/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlBlock.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:32:58 by haeem             #+#    #+#             */
/*   Updated: 2023/11/20 19:50:04 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ControlBlock.h"

void	loop_rt(t_control_block *cb)
{
	cb->mlx.mlx = mlx_init();
	cb->mlx.win = mlx_new_window(cb->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	cb->img.ptr = mlx_new_image(cb->mlx.mlx, IMG_WIDTH, IMG_HEIGHT);
	cb->img.data = (int *)mlx_get_data_addr(cb->img.ptr, &cb->img.bpp,
			&cb->img.size_l, &cb->img.endian);
	reset_img(&cb->img);
	init_render_scene(&cb->scene);
	render_scene(&cb->scene, &cb->img, 0);
	mlx_put_image_to_window(cb->mlx.mlx, cb->mlx.win, cb->img.ptr, 0, 0);
	hooks(cb);
	mlx_loop(cb->mlx.mlx);
}
