/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlBlock.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:32:58 by haeem             #+#    #+#             */
/*   Updated: 2023/11/14 21:34:00 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLBLOCK_H
# define CONTROLBLOCK_H

# include "mlx.h"
# include "Image.h"
# include "Scene.h"

typedef struct s_control_block
{
	t_mlx	mlx;
	t_img	img;
	t_scene	scene;
}t_control_block;

void	loop_rt(t_control_block *cb);

#endif
