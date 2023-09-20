/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/02 20:23:43 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_strin(char **strin)
{
	if (strin[0] != NULL)
		free(strin[0]);
	if (strin[1] != NULL)
		free(strin[1]);
	free(strin);
}
void	ft_free_quo(t_data *data)
{
	t_quo	*aux;
	t_quo	*temp;

	aux = data->quo;
	while (aux != NULL)
	{
		temp = aux;
		aux = aux->next;
		free(temp);
	}
}

