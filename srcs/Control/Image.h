/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by haeem             #+#    #+#             */
/*   Updated: 2023/11/20 20:32:46 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "mlx.h"

# define WIN_WIDTH 2560
# define WIN_HEIGHT 1300

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