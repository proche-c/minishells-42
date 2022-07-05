/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 15:43:23 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_envp *envp) 
{
	// printf("FT_ENV\n");
	while (envp != NULL)
	{
		if (envp->type == 1) // 1 = (pepe="xd") || 2 = (pepe=) || 3 = (pepe)
		{
			printf("%s=%s\n", envp->key, envp->value);
		}
		else if (envp->type == 2)
		{
			printf("%s=\n", envp->key);
		} // Si no es 1 o 2 no se va a imprimir 
		envp = envp->next;
	}
}