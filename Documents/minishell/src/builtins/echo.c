/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 13:42:06 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_data *data) // PROBABLEMENTE SE TENGA QUE MODIFICAR A DOS ARGS DE ENTRADA, (-rn textoxd)
{
	t_down	*temp;

	temp = data->down;
	if (ft_strncmp(temp->arg, "-n", 2) == 0) // sin salto de linea
	{
		temp = temp->next;
		while (temp != NULL)
		{
			write(1, temp->arg, ft_strlen(temp->arg));
			temp = temp->next;
			if (temp != NULL)
				write(1, " ", 1);
		}
	}
	else
	{
		while (temp != NULL)
		{
			write(1, temp->arg, ft_strlen(temp->arg));
			temp = temp->next;
			if (temp != NULL)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	
}