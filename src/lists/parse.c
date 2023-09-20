/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*   By: proche-c <proche-c@student.42barcelona.  +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:22:13 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_new_cmd(t_master *master)
{
	t_data	*list;

	list = (t_data *)malloc(sizeof(t_data));
	if (list == NULL)
	{
		master->error = 1;
		return (NULL);
	}
	list->type = 0;
	list->num_args = 0;
	list->cmd = NULL;
	list->next = NULL;
	list->args = NULL;
	list->down = NULL;
	list->quo = NULL;
	return (list);
}

t_quo	*ft_new_quo(void)
{
	t_quo	*quo;

	quo = (t_quo *)malloc(sizeof(t_quo));
	if (quo == NULL)
		return (NULL);
	quo->pos = -1;
	quo->first = 0;
	quo->next = NULL;
	return (quo);
}

t_down	*ft_down_new(t_master *master, char *str)
{
	t_down	*down;

	down = (t_down *)malloc(sizeof(t_down));
	if (down == NULL)
	{
		master->error = 1;
		return (NULL);
	}
	down->arg = ft_strdup(str);
	//printf("puntero down->arg: %p\n", down->arg);
	down->next = NULL;
	return (down);
}
