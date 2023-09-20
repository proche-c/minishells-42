/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/07/02 20:23:43 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_pipes(t_master *master)
{
	int x;
	
	x = 0;
	if (master->pipes)
	{
		x = 0;
		while (x < master->num_pipes)
		{
			free(master->pipes[x]);
			x++;
		}
		free(master->pipes);
	}
}

void	ft_clean_elem_char(t_master *master)
{
	// int	x;

	// x = 0;
	if (master->elem) // Resultado de split raro
	{
		// while (master->elem[x])
		// {
		// 	printf("master->elem[%d]: %s\n", x, master->elem[x]);
		// 	free(master->elem[x]);
		// 	x++;
		// }
		free(master->elem);
		master->elem = NULL;
	}
}

/*
	list
	envp - Se libera al final
	str
	elem
	bin_paths - Solo se usa dentro de los forks
	env - Se libera al final
	pipes
	home - Se libera al final
*/
void	ft_clean_master_middle(t_master *master)
{
	print("INICIANDO LIMPIEZA\n");
	if (ft_spaces(master->str) == 1) //ESTO ME GENERA UN LEAK
		return ;
	print("CLEAN2\n");
	ft_clean_list(master);
	print("CLEAN3\n");
	print("MASTER->STR == (%p)", master->str);
	if (master->str)
	{
		free(master->str);
		master->str = NULL;
	}
	print("CLEAN4\n");
	ft_clean_elem_char(master);
	print("CLEAN5\n");
	ft_clean_pipes(master);
	print("CLEAN6\n");
}


/*
	list
	envp
	str
	elem
	bin_paths - Solo se usa dentro de los forks
	env
	pipes
	home
*/
void	ft_clean_master_all(t_master *master)
{

	ft_clean_list(master);

	// envp
	ft_clean_envp(master); // Nuevo free, solo libera el primero
	// envp end

	if (master->str)
	{
		free(master->str);
		master->str = NULL;
	}

	ft_clean_elem_char(master);

	// env
	// ft_clean_env_char(master); // En construccion
	// env end

	ft_clean_pipes(master);

	// home
	if (master->home)
		free(master->home);
}

void	ft_clean_env_char(t_master *master)
{
	int	x;

	x = 0;
	if (!master->env)
		return ;
	while (master->env[x])
	{
		free(master->env[x]);
		x++;
	}
	free(master->env);
	master->env = NULL;
}

void	ft_clean_envp(t_master *master)
{
	t_envp	*list;
	t_envp	*temp;

	list = master->envp;
	if (list->next)
		temp = list->next;
	else
		temp = NULL;
	while (list)
	{
		ft_clean_envp_node(list);
		if (temp)
		{
			list = temp;
		}
		else
		{
			list = NULL;
		}
		if (list && list->next)
			temp = list->next;
		else
			temp = NULL;
	}
}

	// 	CODIGO VICTOR
	// ft_clean_elem_victor(elem); // DESCOMENTADO VICTOR
	// if (elem)
	// 	free(elem);

// void	ft_clean_elem_victor(t_elem *elem) // PROBANDO LIMPIAR CODIGO DE PAULA
// {
// 	int	i;

// 	printf("FT_CLEAN_ELEM\n");
// 	i = 0;
// 	printf("FT_CLEAN_ELEM 2 == (%p)\n", elem->str);
// 	// if (elem->str)
// 	// 	free(elem->str);
// 	printf("FT_CLEAN_ELEM\n");
// 	if (elem->num_cmds > 0)
// 	{
// 		while (i < elem->num_cmds)
// 		{
// 			printf("FT_CLEAN_ELEM == (%p)\n", elem->cmds[i]);
// 			if (elem->cmds[i])
// 				free(elem->cmds[i]);
// 			i++;
// 		}
// 	}
// 	printf("FT_CLEAN_ELEM 4 == (%p)\n", elem->cmds);
// 	if (elem->cmds)
// 		free(elem->cmds);
// 	printf("FT_CLEAN_ELEM\n");
// }
