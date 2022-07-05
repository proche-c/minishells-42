/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_entry	*ft_get_new_entry(t_entry *entry, char **cmds, int i)
{
	t_data *new_data;
	t_entry *new_entry;

	new_data = malloc(sizeof(t_data *));
	new_entry = malloc(sizeof(t_entry *));
	new_data->cmd = ft_split(cmds[i], ' ');
	entry->next = new_entry;
	new_entry->data = new_data;
	new_entry->next = NULL;
	return (new_entry);
}

void ft_get_entries(t_entry *entry, int num_elem, char **cmds)
{
	int i;

	i = 1;
	while (i < num_elem)
	{
		ft_get_new_entry(entry, cmds, i);
		if (i < num_elem - 1)
			entry = entry->next;
		i++;
	}
}

t_entry	*ft_get_first_entry(char **cmds, int num_elem, t_entry *first)
{
	t_data	*data;
	t_entry *entry;

	data = malloc(sizeof(t_data *));
	entry = malloc(sizeof(t_entry *));
	if (!data || !entry)
		ft_error_3(cmds, data, entry, first);
	else
	{
		data = ft_get_data(data, cmds[0], first, entry);
		if (data)
		{
			first = entry;
			entry->data = data;
			entry->next = NULL;
			ft_get_entries(entry, num_elem, cmds);
			ft_free_cmds(cmds);
			return (first);
		}
	}
	return(NULL);
}

void	ft_get_entry(char *str)
{
	char	**cmds;
	int		num_pipes;
	int		num_elem;
	t_entry *first;
	int i;

	str = ft_check_str(str);
	num_pipes = ft_get_num_pipes(str);
	num_elem = num_pipes + 1;
	cmds = ft_split(str, '|');

	if (ft_eval_pipes(cmds, str) == 0 && ft_eval_redir(cmds) == 0)
	{
		free(str);
		first = malloc(sizeof(t_entry *));
		if (!first)
			ft_error_2(first, cmds);
		first = ft_get_first_entry(cmds, num_elem, first);
		while (first)
		{
			i = 0;
			while (first->data->cmd[i])
			{
				printf("%s\n", first->data->cmd[i]);
				i++;
			}
			first = first->next;
		}
	}
}







