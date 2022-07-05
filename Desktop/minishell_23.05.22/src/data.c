/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data *ft_get_d_redir(t_data *data, char *sep, char *line)
{
	char **pre_cmds;

	if (ft_eval_redir(sep) == 0)
	{
		if (sep[0] == '>' && sep[1] == '>')
		{
			data->cmd = (char **)malloc(sizeof(char *));
			data->cmd = 0;
			data->file_in->name = ft_split(line, '>');
			//ft_get_array_d_redir(sep);
		}
		else
		{
			pre_cmds = ft_split(line, '>');
			data->cmd = ft_split(pre_cmds[0], ' ');
			//ft_get_array_d_redir(sep);
		}
		return(data);
	}
	else
		return(NULL);
}

t_data 	*ft_get_data(t_data *data, char *line, t_entry *first, t_entry *entry)
{
	char *sep;

	sep = ft_strnstr(line, ">>", ft_strlen(line));
	printf("sep is %s\n", sep);
	if (sep != NULL)
	{
		data = ft_get_d_redir(data, sep, line);
		if (data == NULL)
			ft_error_4(data, entry, first);
		return (data);
	}

	/*if (ft_find_char(cmd, '>') == 1)
	{
		data->file_out = 1;
		ft_split(cmd, '>');


	}
	data->cmd = ft_split(cmd, ' ');*/
	else
	{
		data->cmd = ft_split(line, ' ');
	}
	return (data);
}








