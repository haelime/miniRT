/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ControlBlock.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:32:58 by haeem             #+#    #+#             */
/*   Updated: 2023/11/20 19:02:58 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLBLOCK_H
# define CONTROLBLOCK_H

# include "mlx.h"
# include "Image.h"
# include "Scene.h"
# include <stdbool.h>

typedef struct s_control_block
{
	t_mlx	mlx;
	t_img	img;
	t_scene	scene;
	bool	is_debug;
}t_control_block;

void	loop_rt(t_control_block *cb);
void	hooks(t_control_block *cb);

#endif
