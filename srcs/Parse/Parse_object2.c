/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_object2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:02:17 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 18:55:19 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Parse.h"
#include "Scene.h"
#include "libft.h"
#include "get_next_line_bonus.h"
#include "Sphere.h"

/* 평면

 pl	0.0,0.0,-10.0	0.0,1.0,0.0	0,0,225
구별자 : pl
x,y,z 좌표 : 0.0, 0.0, -10.0
정규화된 삼차원 방향 벡터. 각 x, y, z 축 마다 [-1, 1] 의 범위를 가짐 : 0.0, 0.0, 1.0
R,G,B 색 범위 [0, 255] : 0, 0, 255 */
void	parse_plane(char *line, t_scene *scene);

void	parse_square(char *line, t_scene *scene);
void	parse_cylinder(char *line, t_scene *scene);
