/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veaz <veaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/06/05 20:52:50 by veaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == 32)
		return (1);
	return (0);
}

static int	ft_check_sign(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = ft_check_sign(str[i]);
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		num = str[i] - 48;
		result = result * 10 + num;
		i++;
	}
	return (result * sign);
}
