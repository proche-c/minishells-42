/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/31 13:23:18 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char *str) // PROBABLEMENTE SE TENGA QUE MODIFICAR A DOS ARGS DE ENTRADA, (-rn textoxd)
{
	// printf("RECIBIENDO EN ECHO == (%s)\n", str);
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		str = str + 3;
		write(1, str, ft_strlen(str));
	}
	else
	{
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	
}