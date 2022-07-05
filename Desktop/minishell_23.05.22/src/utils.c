/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int 	ft_get_num_pipes(char *str)
{
	int	num_pipes;
	int	i;

	num_pipes = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			num_pipes++;
		i++;
	}
	return (num_pipes);
}

char *ft_check_str(char *str)
{
	int len;
	char *str_add;

	len = ft_strlen(str);
	while(str[len - 1] == '|' && str[len - 2] != '|')
	{
		str_add = readline(ANSI_COLOR_SHELL"🤖 Pipe ➤ "ANSI_COLOR_RESET);
		str = ft_strjoin(str,str_add);
		len = ft_strlen(str);
	}
	return(str);
}

int ft_find_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}






