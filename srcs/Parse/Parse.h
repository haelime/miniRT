/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:50:02 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 19:42:54 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "Scene.h"

void	parse(char *file, t_scene *scene);

void	exit_parse(char *line);
void	free_split(char **split);
float	ft_max3f(float a, float b, float c);
float	ft_atof(const char *str);

#endif /* PARSE_H */