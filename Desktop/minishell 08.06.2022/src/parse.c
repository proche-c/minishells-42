/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_parse_exec(char *str)//Esta funcion llama a ft_get_entry para luego ejecutarla
{
	//int i;
	t_entry *first;

	str = ft_check_str(str);
	str = ft_check_quote(str);
	if (ft_eval_pipes(str) == 1)
		ft_error_1(str);
	else
	{
		first = malloc(sizeof(t_entry *));
		if (first)
		{
			first = ft_get_entry(str, first);
			printf("Type is %d\n", first->data->type);
			printf("Cmd is %s\n", first->data->cmd);
			first = first->next;
						printf("Type is %d\n", first->data->type);
			printf("Cmd is %s\n", first->data->cmd);
						first = first->next;
						printf("Type is %d\n", first->data->type);
			printf("Cmd is %s\n", first->data->cmd);
			//i = 0;
			/*if (first->data->args)
			{
				while (first->data->args[i])
				{
					printf("arg %d is %s\n", i, first->data->args[i]);
					i++;
				}
			}*/
			//if (first)
				//ft_execute(first);
		}
	//free (str);
	//free(first);
	}
}



			/*printf("Type is %d\n", first->data->type);
			printf("Cmd is %s\n", first->data->cmd);
			i = 0;
			if (first->data->args)
			{
				while (first->data->args[i])
				{
					printf("arg %d is %s\n", i, first->data->args[i]);
					i++;
				}
			}*/