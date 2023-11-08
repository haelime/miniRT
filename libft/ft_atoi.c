/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:22:58 by haeem             #+#    #+#             */
/*   Updated: 2023/11/08 19:33:30 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ans;

	i = 0;
	sign = 1;
	ans = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{	
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return (ans * sign);
}

long	ft_atol(const char *str)
{
	int		i;
	long	sign;
	long	ans;

	i = 0;
	sign = 1;
	ans = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{	
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return ((long)ans * sign);
}

long long	ft_atoll(const char *str)
{
	int			i;
	long long	sign;
	long long	ans;

	i = 0;
	sign = 1;
	ans = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{	
		ans *= 10;
		ans += str[i] - '0';
		i++;
	}
	return ((long long)ans * sign);
}
