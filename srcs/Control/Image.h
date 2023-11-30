/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by haeem             #+#    #+#             */
/*   Updated: 2023/11/30 14:46:26 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "mlx.h"

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

# define IMG_WIDTH 640
# define IMG_HEIGHT 480

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

#endif