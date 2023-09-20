/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:26:41 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pre_while(t_master *master, t_data *list)
{
	ft_create_pipes(master);
	ft_complete_char_to_execute(master);
	ft_num_cmds(master);
	if (master->num_redir >= 1)
	{
		ft_fix_args(master, list);
		ft_complete_char_to_execute(master);
	}
}

static t_data	*ft_idk(t_data *list)
{
	if (list->next)
		if (list->next->next)
			if (list->next->next->next)
				list = list->next->next->next;
	return (list);
}

t_data	*ft_check_pre_execute(t_master *master, t_data *list)
{
	int		check;

	check = 0;
	if (!list || list == NULL)
		return (NULL);
	master->redir_type = 0;
	if (master->execute == 0)
		return (NULL);
	if (list->type == 1)
	{
		list = list->next;
		master->executed_pipes++;
	}
	check = master->executed_cmds;
	list = ft_redirections(master, list);
	if (master->num_cmds < 1)
		return (NULL);
	if (check != master->executed_cmds)
		return (ft_idk(list));
	return (list);
}

void	ft_get_args_for_execve2(t_data *list_node)
{
	t_data	*aux;
	t_down	*aux_down;
	int		i;

	i = 0;
	aux = list_node;
    aux->args = malloc(sizeof(char *) * 7); //ERROR PORQUE SIEMPRE 7
	if (!aux->args)
		return ;
	aux->args[i] = ft_strdup(list_node->cmd);
	aux_down = aux->down;
	i++;
	while (aux_down)
	{
		aux->args[i] = ft_strdup(aux_down->arg);
		aux_down = aux_down->next;
		i++;
	}
	aux->args[i] = 0;
}

void	ft_complete_char_to_execute(t_master	*master)
{
	struct s_data	*aux;
	int				x;

	x = 0;
	aux = master->list;
	while (aux)
	{
		x = 0;
		if (aux->type != PIPE && aux->type == 0)
		{
			ft_get_args_for_execve2(aux);
			while (aux->args[x] != NULL)
				x++;
		}
		aux = aux->next;
	}
}
