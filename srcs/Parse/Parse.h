/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:50:02 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/06 20:21:45 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "Scene.h"

void	parse(char *file, t_scene *scene);

void	exit_parse(char *line);

#endif /* PARSE_H */
