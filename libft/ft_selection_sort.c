/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selection_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:47:25 by haeem             #+#    #+#             */
/*   Updated: 2023/11/05 20:28:17 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	ft_selection_sort(int arr[], int n)
{
	int	i;
	int	j;
	int	min_idx;

	i = -1;
	while (++i < n - 1)
	{
		min_idx = i;
		j = i;
		while (++j < n)
			if (arr[j] < arr[min_idx])
				min_idx = j;
		ft_swap(&arr[min_idx], &arr[i]);
	}
}
