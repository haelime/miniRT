/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:57:54 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/12/12 20:24:33 by haeem            ###   ########seoul.kr  */
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

void	norminette_atof(const char **str, int *neg, float *scale, int *afterdot)
{
	*afterdot = 0;
	*scale = 1.0;
	*neg = 0;
	if (validate_str(*str) == 0)
		exit_parse(NULL);
	if (**str == '-')
	{
		(*str)++;
		*neg = 1;
	}
	else if (**str == '+')
		(*str)++;
}

float	norminette2_atof(int *neg, float *val)
{
	if (*neg)
		return (-(*val));
	else
		return (*val);
}

float	ft_atof(const char *str)
{
	int		afterdot;
	int		neg;
	float	val;
	float	scale;

	norminette_atof(&str, &neg, &scale, &afterdot);
	val = 0.0f;
	while (*str != '\n' && *str != '\0')
	{
		if (afterdot)
		{
			scale = scale / 10;
			val = val + (*str - '0') * scale;
		}
		else
		{
			if (*str == '.')
				afterdot++;
			else
				val = val * 10.0 + (*str - '0');
		}
		str++;
	}
	return (norminette2_atof(&neg, &val));
}
