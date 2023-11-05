/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:16:05 by haeem             #+#    #+#             */
/*   Updated: 2023/11/05 20:31:45 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	deque_clear(t_deque *deque)
{
	while (deque->size)
		deque_pop_front(deque);
}

void	deque_free(t_deque *deque)
{
	deque_clear(deque);
	free(deque);
}

void	deque_init(t_deque *deque)
{
	deque->size = 0;
	deque->front = NULL;
	deque->back = NULL;
}
