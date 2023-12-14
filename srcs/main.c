/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:50:50 by haeem             #+#    #+#             */
/*   Updated: 2023/12/14 16:32:40 by haeem            ###   ########seoul.kr  */
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

	if (argc != 2)
	{
		ft_putstr_fd("Error\n", STDOUT_FILENO);
		return (0);
	}
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