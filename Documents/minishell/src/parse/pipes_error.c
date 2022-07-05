/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/09 11:10:07 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_eval_pipes(char *str)
{
	int	i;

	if (str[0] == '|')
		return (1);
	i = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '|' && str[i - 1] == '|')
			return (1);
	}
	i = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == '|')
				return (1);
		}
	}
	return (0);
}
