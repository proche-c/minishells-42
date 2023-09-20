/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:18:14 by vaguilar          #+#    #+#             */
/*   Updated: 2022/02/09 12:18:22 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"
#include "../../../include/minishell.h"

int	print(const char *s, ...)
{
	va_list	args;
	int		count;

	if (DEBUG == 0)
		return (0);
	va_start(args, s);
	count = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (*(s + 1) == '%')
				count += ft_putchar('%');
			else
				count += ft_printargs(s, args);
			s = s + 2;
		}
		else
		{
			count += ft_putchar(*s);
			s++;
		}
	}
	ft_putchar('\n');
	va_end(args);
	return (count);
}

int	printa(const char *s, ...)
{
	va_list	args;
	int		count;

	if (DEBUG_2 == 0)
		return (0);
	va_start(args, s);
	count = 0;
	while (*s)
	{
		if (*s == '%')
		{
			if (*(s + 1) == '%')
				count += ft_putchar('%');
			else
				count += ft_printargs(s, args);
			s = s + 2;
		}
		else
		{
			count += ft_putchar(*s);
			s++;
		}
	}
	ft_putchar('\n');
	va_end(args);
	return (count);
}