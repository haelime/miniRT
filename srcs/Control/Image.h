/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by haeem             #+#    #+#             */
/*   Updated: 2023/11/08 20:35:08 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "../../mlx/mlx.h"

# define WIN_WIDTH 2560
# define WIN_HEIGHT 1300

# define IMG_WIDTH 1920
# define IMG_HEIGHT 1060

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width_max;
	int		height_max;
}t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}t_mlx;

void	reset_img(t_img *img);
void	draw_rt();

#endif