/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:21:16 by haeem             #+#    #+#             */
/*   Updated: 2023/11/14 18:37:17 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "Image.h"
#include "Scene.h"

void	reset_img(t_img *img)
{
	int	i;

	i = -1;
	while (++i < IMG_WIDTH * IMG_HEIGHT)
		img->data[i] = 0;
}


// void	make_image(t_img *img, t_mlx *mlx)
// {
// 	int	x;
// 	int	y;

// 	y = -1;
// 	reset_img(img);
	// while (++y < IMG_HEIGHT)
	// {
	// 	x = -1;
	// 	while (++x < IMG_WIDTH)
	// 	{
	// 		if (0 <= x && 0 <= y && x < IMG_WIDTH && y < IMG_HEIGHT)
	// 		{
	// 			img->data[x + y * IMG_WIDTH] = 255;
	// 		}
	// 	}
	// }
	// render_scene(scene);
// 	mlx_put_image_to_window(mlx->mlx, mlx->win, img->ptr, 0, 0);
// }


