/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/08 22:26:14 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_down_node(t_down *down)
{
	if (down->arg)
		free(down->arg);
	if (down->next)
		free(down->next);
}

void ft_clean_data(t_data *list)
{
	list->type = -1;
}

void	ft_clean_data_node(t_data *data)
{
	int	x;

	x = 0;
	print("FT_CLEAN_DATA_NODE1 (%s)\n", data->cmd);
	if (data->cmd)
		free(data->cmd);
	print("FT_CLEAN_DATA_NODE2\n");
	// printf("DATA NUM ARGS = (%i)\n", data->num_args);
	// if (data->args)
	// 	printf("SI EXISTOOOO\n");
	// else
	// 	printf("NO EXISTOOOO\n");
	// printf("DATA->ARGS %p", data->args);
	// printf("DATA->ARGS[x] %p", data->args[0]);
	// printf("DATA->ARGS %p", data->args);
	// printf("DATA->ARGS[x] %p", data->args[0]);
	// printf("END");
	if (data->args)
	{
		print("FT_CLEAN_DATA_NODE3\n");
		if (data->args[x])
		{
			while(data->args[x])
			{
				free(data->args[x]);
				x++;
			}
		}
		free(data->args);
	}
	print("FT_CLEAN_DATA_NODE4\n");
	if (data->down)
	{
		print("FT_CLEAN_DATA_NODE4.1\n");
		ft_clean_down_node(data->down);
		print("FT_CLEAN_DATA_NODE4.2\n");
		free(data->down);
		print("FT_CLEAN_DATA_NODE4.3\n");
		data->down = NULL;
		print("FT_CLEAN_DATA_NODE4.4\n");
	}
	print("FT_CLEAN_DATA_NODE5\n");
}

void	ft_clean_list(t_master *master)
{
	t_data 	*list;
	t_data	*temp;

	list = master->list;
	temp = NULL;
	print("FT_CLEAN_LIST1");
	if (list)
	{
		print("FT_CLEAN_LIST2");
		if (list && list->next)
			temp = list->next;
		print("FT_CLEAN_LIST3");
		while (list)
		{
			print("FT_CLEAN_LIST WHILE");
			ft_clean_data_node(list);
			print("INTENTANDO LIBERAR %p", list);
			free(list);
			if (temp)
				list = temp;
			else
				list = NULL;
			if (list && list->next)
				temp = list->next;
			else
				temp = NULL;
		}
		print("FT_CLEAN_LIST4");
		master->list = NULL;
	} 
	print("FT_CLEAN_LIST5");
}

void	ft_clean_envp_node(t_envp *envp)
{
	if (envp->key)
		free(envp->key);
	if (envp->value)
		free(envp->value);
}

void ft_delete_next_node_data(t_data *list) // ESTE SI LO ESTOY USANDO NO ELIMINAR POR FAVOR, EN REDIRECCIONES
{
	t_data *temp;
	t_data *delete;

	temp = list->next->next;
	delete = list->next;
	ft_clean_data(delete);
	free(delete);
	list->next = temp;
}
// void	ft_free_vuns(t_vunset *vuns)
// {
// 	//free(vuns->key);
// 	free(vuns);
// }

// void	ft_free_vuns_all(t_master *master)
// {
// 	t_vunset *iter;

// 	if (master->initial_vuns->first == 2)
// 	{
// 		while (master->initial_vuns != NULL)
// 		{
// 			iter = master->initial_vuns->next;
// 			ft_free_vuns(master->initial_vuns);
// 			master->initial_vuns = iter;
// 		}
// 	}
// }

void	ft_clean_env(t_master *master)
{
	int	x;

	x = 0;
	while (master->env[x])
	{
		x++;
	}
}

void	ft_clean_master(t_master *master) // Limpieza macro de master, aun debe tener leaks
{
	printa("ENTRO EN FT_CLEAN_MASTER");

	return ;
	t_data	*temp;
	if (master->list)
	{
		temp = master->list;
		while (temp->next != NULL)
		{
			print( RED "NODE TO DELETE (%p)" RESET, temp->next);
			ft_delete_next_node_data(temp);
		}
		print( RED "NODE TO DELETE here(%p)" RESET, temp);
		if (temp)
			ft_clean_data(temp);
		//free(master->list);
	}
	master->list = NULL;

	print("DEBUG 2");
	// if (master->elem)
	// 	free(master->elem);//COMENTADO V
	master->elem = NULL;

	master->num_elem = 0;
	master->num_cmds = 0;
	master->num_redir = 0;
	master->fd_redir = 0;
	master->redir_type = 0;
	master->executed_cmds = 0;
	master->executed_pipes = 0;
	master->error = 0;

	// print("DEBUG 3 (%p)", master->bin_paths);
	// int x = 0;
	// while (master->bin_paths[x])
	// {
	// 	print("while (%p)", master->bin_paths[x]);
	// 	free(master->bin_paths[x]);
	// 	x++;
	// }
	// print("DEBUG 3 (%p)", master->bin_paths);
	// if (master->bin_paths)
	// 	free(master->bin_paths);
	// master->bin_paths = NULL;
	// print("DEBUG 3 (%p)", master->bin_paths);


	int x = 0;
	if (master->pipes && master->num_pipes > 0)
	{
		while(x < master->num_pipes)
		{
			// free(master->pipes[x]); //COMENTADO V
			x++;
		}
		//free(master->pipes);//COMENTADO V
	}
	master->pipes = NULL;
	master->num_pipes = 0;
	master->execute = 1;
	printa("SALGO DE FT_CLEAN_MASTER");
}

void	ft_free_all(t_master *master)
{
	printa("ENTRO EN FT_FREE_ALL");
	t_envp *temp;
	t_envp	*to_delete;
	int x = 0;

	(void)master;
	(void)temp;

	if (master->envp)
	{
		temp = master->envp;
		while (temp->next)
		{
			to_delete = temp->next;
			temp->next = to_delete->next;
			//ft_clean_envp(to_delete);
		}
		//ft_clean_envp(temp);
	}
	int	len = ft_len_envp(master->env);
	while (x < len)
	{
		//free(master->env[x]);//COMENTADO V
		x++;
	}
	//free(master->env);//COMENTADO V
	printa("SALGO DE FT_FREE_ALL");
}