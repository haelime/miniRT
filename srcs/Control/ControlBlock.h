/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlBlock.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:32:58 by haeem             #+#    #+#             */
/*   Updated: 2023/11/14 18:39:28 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_BLOCK_H
# define CONTROL_BLOCK_H

# include "mlx.h"
# include "Image.h"
# include "Scene.h"

typedef struct s_control_block
{
	t_mlx	mlx;
	t_img	img;
	t_scene	scene;
}t_control_block;

void	loop_rt(t_control_block* cb);

#endif
