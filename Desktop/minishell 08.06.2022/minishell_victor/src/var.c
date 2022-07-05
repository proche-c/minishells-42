/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/16 19:37:02 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_var(char *str) //RECIBE EL NOMBRE DE LA VARIABLE Y RETORNA SU VALOR
{
	char	*value;

	value = getenv(str);
	/*if (value)
		printf("VALOR == (%s)\n", value);
	else
		write(1, "\n", 1);*/
	return(value);
}