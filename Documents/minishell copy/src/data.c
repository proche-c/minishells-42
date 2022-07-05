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

t_data 	*ft_get_data(t_data *data, char **cmds, t_entry *first, t_entry *entry)
{
	int i;
	char **pre_cmds;
	char *sep;
	(void)first;
	(void)entry;

	sep = malloc(sizeof(char) * ft_strlen(cmds[0]));
	sep = ft_strnstr(cmds[0], ">>", ft_strlen(cmds[0]));
	printf("me queda   %s\n", sep);
	if (sep != NULL)
	{
		if (ft_eval_redir(data, cmds, first, entry) == 0)
		{
			pre_cmds = ft_split(cmds[0], '>');
			data->cmd = ft_split(pre_cmds[0], ' ');
			i = 0;
			while (data->cmd[i])
			{
				printf("      %s\n", data->cmd[i]);
				i++;
			}
			printf("me queda   %s\n", sep);
		}
		return(data);
	}

	/*if (ft_find_char(cmd, '>') == 1)
	{
		data->file_out = 1;
		ft_split(cmd, '>');


	}
	data->cmd = ft_split(cmd, ' ');*/
	return (NULL);
}

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

t_entry	*ft_get_first_entry(char **cmds, int num_elem, t_entry *first)
{
	t_data	*data;
	t_entry *entry;
	int i;

	data = malloc(sizeof(t_data *));
	entry = malloc(sizeof(t_entry *));
	if (!data || !entry)
		ft_error_3(cmds, data, entry, first);
	else
	{
		data = ft_get_data(data, cmds, first, entry);
		//data->cmd = ft_split(cmds[0], ' ');
		first = entry;
		entry->data = data;
		entry->next = NULL;
		i = 1;
		while (i < num_elem)
		{
			ft_get_new_entry(entry, cmds, i);
			if (i < num_elem - 1)
				entry = entry->next;
			i++;
		}
		ft_free_cmds(cmds);
		entry = first;
		while(entry)
		{
			i = 0;
			while(entry->data->cmd[i])
			{
				printf("%s\n", entry->data->cmd[i]);
				i ++;
			}
			entry = entry->next;
		}
		return (first);
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
	i = 0;
	while (cmds[i])
	{
		printf("%s\n", cmds[i]);
		i++;
	}
	if (ft_eval_pipes(cmds, str) == 0)
	{
		free(str);
		first = malloc(sizeof(t_entry *));
		if (!first)
			ft_error_2(first, cmds);
		first = ft_get_first_entry(cmds, num_elem, first);
	}

}







