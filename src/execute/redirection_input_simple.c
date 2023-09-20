/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:33:16 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_type_3(t_master *master, char *file_name)
{
	ft_return_error(file_name, ": Permission denied\n");
	master->executed_cmds++;
	master->execute = 0;
	master->error = 1;
	g_returnvalue = 1;
}

t_data	*ft_is_type_3_and_i_cant_access(t_master *master, t_data *list)
{
	ft_return_error(list->next->cmd, ": No such file or directory\n");
	master->executed_cmds++;
	if (master->num_pipes == 0)
	{
		master->execute = 0;
		master->error = 1;
	}
	else
	{
		while (list)
		{
			if (list->type == PIPE)
			{
				master->executed_pipes++;
				list = list->next;
				return (list);
			}
			list = list->next;
		}
	}
	return (NULL);
}

static t_data	*ft_is_redir_3(t_master *master, t_data *list)
{
	t_data	*temp;

	temp = list;
	if (list->next->type == 3
		&& access(list->next->next->cmd, F_OK) == 0
		&& access(list->next->next->cmd, R_OK) != 0)
		ft_is_type_3(master, list->next->next->cmd);
	else if (list->type == 3 && access(list->next->cmd, F_OK) != 0)
	{
		temp = ft_is_type_3_and_i_cant_access(master, list);
		if (temp)
			return (temp);
		return (list);
	}
	else if (list->type == 3 && access(list->next->cmd, F_OK) == 0)
	{
		master->executed_cmds++;
		return (list);
	}
	if (master->num_pipes == 0)
	{
		if (list->next->type == 3 && access(list->next->next->cmd, F_OK) != 0)
		{
			ft_return_error(list->next->next->cmd,
				": No such file or directory\n");
			master->executed_cmds++;
			master->error = 1;
			g_returnvalue = 1;
			return (list);
		}
	}
	return (list);
}

static t_data	*ft_no_pipes(t_master *master, t_data *list)
{
	if (list->next->type == 3 && access(list->next->next->cmd, F_OK) != 0)
	{
		ft_return_error(list->next->next->cmd,
			": No such file or directory\n");
		master->executed_cmds++;
		master->error = 1;
		g_returnvalue = 1;
		return (list);
	}
	return (NULL);
}

static t_data	*ft_while_rare(t_master *master, t_data *list)
{
	t_data	*temp;
	t_data	*redir;
	t_data	*next_redir;

	temp = list;
	redir = temp->next;
	next_redir = redir->next;
	while (temp && next_redir)
	{
		if (access(next_redir->cmd, F_OK) == 0)
		{
			next_redir = next_redir->next;
			if (!next_redir || next_redir->type == PIPE)
				break ;
			temp = temp->next->next;
			redir = temp->next;
			if (redir)
				next_redir = redir->next;
			else
				break ;
		}
		else
		{
			ft_return_error(next_redir->cmd, ": No such file or directory\n");
			master->executed_cmds += 1;
			if (master->num_pipes == 0)
			{
				master->execute = 0;
				master->error = 1;
			}
			else
			{
				while (list)
				{
					if (list->type == PIPE)
					{
						master->executed_pipes++;
						list = list->next;
						return (list);
					}
					list = list->next;
				}
				if (!list)
					master->execute = 0;
			}
			break ;
		}
	}
	return (NULL);
}

t_data	*ft_redir_input_simple(t_master *master, t_data *list)
{
	t_data	*temp;

	temp = list;
	master->redir_type = 3;
	if (list->next->type == 3 || list->type == 3)
		ft_is_redir_3(master, list);
	if (master->num_pipes == 0)
		ft_no_pipes(master, list);
	temp = ft_while_rare(master, list);
	if (temp)
		return (temp);
	if (master->execute == 0 || master->error == 1)
		return (list);
	if (list->next->next->cmd && access(list->next->next->cmd, F_OK) == 0
		&& master->num_pipes > 0)
		master->fd_redir = open(list->next->next->cmd, O_RDONLY);
	else
		master->fd_redir = open(list->next->next->cmd, O_RDONLY);
	return (list);
}