/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:50:50 by haeem             #+#    #+#             */
/*   Updated: 2023/11/15 22:12:19 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "Parse.h"
#include "Image.h"
#include "ControlBlock.h"

int	main(int argc, char **argv)
{
	static t_control_block	cb;

	if ((argc != 2 && argc != 3)
		|| (argc == 3 && ft_strcmp(argv[1], "--save") != 0))
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		return (0);
	}
	if (argc == 3 && ft_strcmp(argv[1], "--save") == 0);
		// TODO
	parse(argv[1], &cb.scene);
	loop_rt(&cb);
	return (0);
}

// open, close, read, write,
// printf, malloc, free, perror,
// strerror, exit
// • All functions of the math
// library (-lm man man 3 math)
// • All functions of the MinilibX