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

void	ft_error_4(char **cmds, t_data *data, t_entry *entry, t_entry *first)
{
	//(void)cmds;
	//(void)data;
	//(void)entry;
	printf("error4\n");
	ft_free_cmds(cmds);
	if (data)
		free(data);
	if (entry)
		free(entry);
	if (first)
		free(first);
}

void	ft_error_3(char **cmds, t_data *data, t_entry *entry, t_entry *first)
{
	printf("error3\n");
	ft_free_cmds(cmds);
	if (data)
		free(data);
	if (entry)
		free(entry);
	if (first)
		free(first);
}

void 	ft_error_2(t_entry *first, char **cmds)
{
	printf("error2\n");
	if (first)
		free(first);
	ft_free_cmds(cmds);
	exit(1);
}

void 	ft_error_1(char **cmds)
{
	ft_free_cmds(cmds);
	printf("error1\n");
	printf("parse error near `|'");
}

void	ft_free_cmds(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		if(cmds[i])
			free(cmds[i]);
		i++;
	}
	if (cmds)
		free(cmds);
}