/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 20:49:25 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_value_master(t_master *master, char *str) //Creo la estructura y verifico str
{
	master->str = str;
	master->error = 0;
	ft_check_str(master);
	ft_check_quote(master);
	//ft_create_envp(master, envp);
}

// void	ft_parse_exec(t_master *master, char *str) //Esta funcion llama a ft_get_entry para luego ejecutarla
// {
// 	//t_master	master;
// 	t_data	*list;
// 	int	x;

// 	x = 0;
// 	// printf("NUM_ELEM == (%d)\n", master->num_elem);
// 	char *const args[] = {"ls", "-la", "/bin", 0};// TEST

	
// 	list = master->list;
// 	while (x < master->num_elem)
// 	{
// 		printf("COMANDO (%i) TYPE == (%i)\n", x, list->type);
// 		if (ft_strncmp(list->cmd, "ls", 2) == 0)
// 		{
// 			//printf("LS ENCONTRADO\n");
// 			if (execve("/bin/ls", args, envp) == -1)
// 				printf("ERROR\n");
// 			else
// 				printf("NO ERROR\n");
// 		}
// 		list = list->next;
// 		x++;
// 	}
// }*/

/*void ft_execute(t_master *master, char **envp)
{
	if (master->list->type == 0)
		ft_execute_cmd(master, envp);
}*/

void	ft_parse_exec(t_master *master, char *str, char **envp) //Esta funcion llama a ft_get_entry para luego ejecutarla
{
	//t_master	master;
	//int i;

	if (ft_eval_pipes(str) == 1) //Algun tipo de error raro con pipes OJO
		ft_error_1(str);
	else
	{
		ft_value_master(master, str);
		ft_get_entry(master); //Obtener los valores
		// * FALTA * Funcion para verificar errores en el parse && || recorrerlo y obtener detalles importantes
		ft_get_paths(master);
		ft_execute_cmd(master, envp);
	}
	
}
