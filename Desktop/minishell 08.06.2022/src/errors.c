/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_1(char *str)
{
	free(str);
	printf("syntax error near unexpected token `|'\n");
}

void	ft_error_2(char **elem)
{
	int	i;

	i = 0;
	while (elem[i])
	{
		free(elem[i]);
		i++;
	}
	free(elem);
}

void	ft_error_3(char **elem, t_data *data, char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
	ft_error_2(elem);
	free(data);
}

void	ft_error_4(char **elem, t_data *data, char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	free(cmds);
	ft_error_2(elem);
	free(data->cmd);
	free(data);
}

void	ft_error_5(char **elem, t_data *data, char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free(cmds[i]);
		i++;
	}
	i = 0;
	while (data->args[i])
	{
		free(data->args[i]);
		i++;
	}
	free(data->args);
	free(cmds);
	ft_error_2(elem);
	free(data->cmd);
	free(data);
}
