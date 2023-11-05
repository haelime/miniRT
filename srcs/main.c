/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:50:50 by haeem             #+#    #+#             */
/*   Updated: 2023/11/05 20:28:21 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/includes/libft.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "test", 4) == 0)
			printf("test\n");
		else
			printf("not test\n");
	}
	else
		printf("error\n");
	return (0);
}

// open, close, read, write,
// printf, malloc, free, perror,
// strerror, exit
// • All functions of the math
// library (-lm man man 3 math)
// • All functions of the MinilibX