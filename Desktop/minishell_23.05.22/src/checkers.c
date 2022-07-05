/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_eval_pipes(char **cmds, char *str)
{
	int	i;
	int	j;

	if (str[0] == '|')
	{
		printf("parse error near `|'\n");
		ft_free_cmds(cmds);
		return(1);
	}
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '|' && str[i -1] == '|')
		{
			printf("parse error near `|'\n");
			ft_free_cmds(cmds);
			return(1);
		}
		i++;
	}
	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j] == ' ')
			j++;
		if (cmds[i][j] == '\0')
		{
			printf("parse error near `|'\n");
			ft_free_cmds(cmds);
			return(1);
		}
		i++;

	}
	return(0);
}

int ft_eval_redir(char **cmds)
{

	if (sep[ft_strlen(sep) - 1] == '>')
	{
		printf("parse error near `>'\n");
		return(1);
	}
	return(0);
}