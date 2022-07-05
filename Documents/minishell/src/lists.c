/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 17:57:47 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data	*ft_new_cmd(void) // Creo cada nodo para los comandos
{
	t_data	*list;

	list = (t_data *)malloc(sizeof(t_data));
	if (list == NULL)
		return (NULL);
	list->type = 0;
	list->num_args = 0;
	list->cmd = NULL;
	list->next = NULL;
	return (list);
}

t_down	*ft_down_new(char *str) // Creo cada nodo para down
{
	t_down	*down;

	down = (t_down *)malloc(sizeof(t_down));
	if (down == NULL)
		return (NULL);
	down->arg = ft_strdup(str);
	down->next = NULL;
	return (down);
}

t_envp	*ft_new_envp(char *key, char *value) // Creo cada nodo para la lista de envp
{
	t_envp	*envp;

	envp = (t_envp *)malloc(sizeof(t_envp));
	if (envp == NULL)
		return (NULL);
	envp->key = 0;
	envp->key = key;
	envp->value = value;
	envp->next = NULL;
	return (envp);
}

t_envp	*ft_lst_last(t_envp *list)
{
	while (list != NULL)
	{
		if (list->next == NULL)
			return (list);
		list = list->next;
	}
	return (list);
}