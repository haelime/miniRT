/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:50:44 by haeem             #+#    #+#             */
/*   Updated: 2023/11/05 20:28:17 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t cnt)
{
	char		*tmp;
	const char	*s;

	if (dest <= src)
		ft_memcpy(dest, src, cnt);
	else
	{
		tmp = dest;
		tmp += cnt;
		s = src;
		s += cnt;
		while (cnt--)
			*--tmp = *--s;
	}
	return (dest);
}
