/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:50:50 by haeem             #+#    #+#             */
/*   Updated: 2023/11/08 20:37:52 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/minirt.h"
#include "../libft/includes/libft.h"
#include "Parse.h"
#include "Control/Image.h"


int	main(int argc, char **argv)
{
	static t_scene	scene;

	if ((argc != 2 && argc != 3)
		|| (argc == 3 && ft_strcmp(argv[1], "--save") != 0))
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		return (0);
	}
	if (argc == 3 && ft_strcmp(argv[1], "--save") == 0);
		// TODO
	parse(argv[1], &scene);
	draw_rt();
	return (0);
}

// open, close, read, write,
// printf, malloc, free, perror,
// strerror, exit
// • All functions of the math
// library (-lm man man 3 math)
// • All functions of the MinilibX