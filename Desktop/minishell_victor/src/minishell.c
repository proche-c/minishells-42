/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/31 13:39:51 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_create_newenvp(char **envp)
{
	char **newenvp;
	int	x;

	x = 0;
	newenvp = (char **)malloc(sizeof(char *) * (ft_len_envp(envp) + 1));
	if (!newenvp)
		return NULL;
	while (envp[x] != NULL)
	{
		newenvp[x] = ft_strdup(envp[x]);
		x++;
	}
	newenvp[x] = NULL;
	ft_order_envp(newenvp);
	return (newenvp);
}

char	**ft_ver_str(char **envp, char *str)
{
	if (str == NULL) // CONTROL + D, 15
	{
		printf("\r");
		free(envp);
		exit(0);
	}
	else if (ft_strncmp(str, "cd", 2) == 0)
	{
		ft_cd(&str[3]);
	}
	else if (ft_strncmp(str, "echo", 4) == 0)
	{
		ft_echo(&str[5]);
	}
	else if (ft_strncmp(str, "export", 7) == 0 || ft_strncmp(str, "env", 7) == 0) //USO DE EXPORT SOLO Y ENV
	{
		ft_export(envp);
	}
	else if (ft_strncmp(str, "export", 6) == 0) //EXPORTANDO UNA NUEVA VARIABLE SIN ERRORES "export variable" 
	{
		envp = ft_export_with_var(envp, &str[7]);
	}
	else if (ft_strncmp(str, "unset", 5) == 0)
	{
		envp = ft_unset(envp, &str[6]);
	}
	else if (ft_strncmp(str, "pwd", 3) == 0 || ft_strncmp(str, "PWD", 3) == 0)
	{
		printf ("%s\n", ft_pwd());
	}
	else if (ft_strncmp(str, "clear", 5) == 0)
	{
		printf("\033[H\033[J");
	}
	else if (ft_strncmp(str, "exit", 4) == 0)
	{
		free(envp);
		exit(0);
	}
	else
	{
		printf("COMANDO INVALIDO (%s)\n", str);
	}
	return (envp);
}


int	main(int argc, char **argv, char **envp)
{
	char *str;

	envp = ft_create_newenvp(envp); //CREA CON MALLOC Y ORDENA ENVP
	ft_signals(); //INICIALIZA LAS SEÑALES
	while (argc && argv && envp)
	{
		str = readline(ANSI_COLOR_SHELL"🤖 Minishell ➤ "ANSI_COLOR_RESET);
		envp = ft_ver_str(envp, str); //VERIFICO STR Y LO APLICO
		add_history(str);
	}
	return(0);
}

//ft_export(envp); //FUNCION PARA "env" Y "export" sin opciones o argumentos
//ft_var(str); //RECIBE EL NOMBRE DE LA VARIABLE Y RETORNA SU VALOR
//ft_pwd(void) //RETORNA LA DIRECCION ACTUAL