/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:54 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/11/08 20:03:02 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "Parse.h"

float	ft_max3f(float a, float b, float c)
{
	float	max;

	max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return (max);
}

int	validate_str(const char *str)
{
	const char	*tmp = str;

	while (*tmp != '\0')
	{
		if (!ft_isdigit(*tmp) && *tmp != '.' && *tmp != '-'
			&& *tmp != '+' && *tmp != ' ' && *tmp != '\n')
			return (0);
		tmp++;
	}
	return (1);
}

float	ft_atof(const char *str)
{
	long long	integer;
	long long	decimal;
	int			decimal_len;

	if (validate_str(str) == 0)
		exit_parse(NULL);
	decimal_len = 1;
	integer = ft_atoll(str);
	while (*str != '.' && *str != '\0')
		str++;
	if (*str == '\0')
		return (integer);
	str++;
	decimal = ft_atoll(str);
	while (decimal)
	{
		decimal >>= 1;
		decimal_len++;
	}
	decimal = ft_atoll(str);
	return (((float)((integer << decimal_len) + decimal)) / (1 << decimal_len));
}
