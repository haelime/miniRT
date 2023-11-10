/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:31 by haeem             #+#    #+#             */
/*   Updated: 2023/11/10 20:42:17 by hyunjunk         ###   ########.fr       */
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
void	draw_rt(t_scene* scene);

#endif