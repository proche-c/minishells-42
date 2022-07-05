/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 19:38:59 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_master	master;
	char *str;
	//char	*prog_path = "/bin/ls";
	//char *const args[] = {"ls", "-la","/bin", 0};

	//execve(prog_path, args, envp);
	ft_signals();
	ft_create_envp(&master, envp);
	while (argc && argv && envp)
	{
		str = readline(ANSI_COLOR_SHELL"🤖 Minishell ➤ "ANSI_COLOR_RESET);
		if (str == NULL)
		{
			printf("NULL\n");
			free(str);
   			exit(0);
		}
		ft_parse_exec(&master, str, envp);
		add_history(str);
		// ft_parse_exec("ls -la 3er | wc -r 3er2do | echo test2 pepe");
	}
	return(0);
}

//ft_export(envp); //FUNCION PARA "env" Y "export" sin opciones o argumentos
//ft_var(str); //RECIBE EL NOMBRE DE LA VARIABLE Y RETORNA SU VALOR
//ft_pwd(void) //RETORNA LA DIRECCION ACTUAL