/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:21:16 by haeem             #+#    #+#             */
/*   Updated: 2023/11/10 20:52:27 by hyunjunk         ###   ########.fr       */
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


void	make_image(t_img *img, t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	reset_img(img);
	while (++y < IMG_HEIGHT)
	{
		x = -1;
		while (++x < IMG_WIDTH)
		{
			if (0 <= x && 0 <= y && x < IMG_WIDTH && y < IMG_HEIGHT)
			{
				img->data[y * IMG_WIDTH + x] = 255;
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, img->ptr, 0, 0);
}

void	draw_rt(t_scene* scene)
{
	t_mlx	mlx;
	t_img	img;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	img.ptr = mlx_new_image(mlx.mlx, IMG_WIDTH, IMG_HEIGHT);
	img.data = (int *)mlx_get_data_addr(img.ptr, &img.bpp, &img.size_l,
			&img.endian);
	// should put pixels on img.data
	
	//


	make_image(&img, &mlx); // need another arg
	// hooks(mlx.win, &img);
	mlx_loop(mlx.mlx);
}
