/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 19:56:55 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exec_builts(t_master *master)
{
	printf("STR == (%s)\n", master->str);
	if (master->str == NULL) // CONTROL + D, 15
	{
		printf("CREO QUE NUNCA LLEGARA A ESTE NULL\n");
		printf("\r");
		//free(envp);
		exit(0); // OJO CON ESTE EXIT
	}
	else if (ft_strncmp(master->list->cmd, "cd", 3) == 0) // Funcionando bien
	{
		if (master->list->num_args > 0) // Verificacion de que existan argumentos para cd
			ft_cd(master->list->down->arg); // Solo le envio un argumento el resto no tiene importancia
	}
	else if (ft_strncmp(master->list->cmd, "echo", 5) == 0) //Funcionando bien
	{
		ft_echo(master->list); //Le envio todo el nodo del comando
	}
	else if (ft_strncmp(master->list->cmd, "export", 7) == 0) //
	{
		if (master->list->num_args > 0)
		{
			printf("AGREGARE ALGO\n");
			t_envp	*temp;
			int	x;
			x = 0;
			temp = master->envp;
			while (temp != NULL)
			{
				x++;
				temp = temp->next;
			}
			printf("LA LISTA TIENE (%i)\n", x);
			ft_export_with_var(master);
			x = 0;
			temp = master->envp;
			while (temp != NULL)
			{
				x++;
				temp = temp->next;
			}
			printf("LA LISTA TIENE (%i)\n", x);
		}
		else
			ft_export(master->envp);// Si solo es el export lo muestro
	}
	else if (ft_strncmp(master->list->cmd, "env", 4) == 0)
	{
		ft_env(master->envp);
	}
	else if (ft_strncmp(master->str, "unset", 5) == 0)
	{
		//envp = ft_unset(envp, &master->str[6]);
	}
	else if (ft_strncmp(master->str, "pwd", 3) == 0 || ft_strncmp(master->str, "PWD", 3) == 0)
	{
		printf ("%s\n", ft_pwd());
	}
	else if (ft_strncmp(master->str, "clear", 5) == 0)
	{
		printf("\033[H\033[J");
	}
	else if (ft_strncmp(master->str, "exit", 4) == 0)
	{
		//free(envp);
		exit(0);
	}
	else
	{
		printf("COMANDO INVALIDO (%s)\n", master->str);
	}
}

/*
Verificacion del enter, DA SEGMENTATION FAULT

*/