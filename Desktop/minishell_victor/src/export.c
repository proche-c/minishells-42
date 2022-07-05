/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/31 14:01:21 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_add_var_envp(char **envp, char *str) // AGREGA UNA NUEVA VARIABLE A ENVP
{
	char	**newenvp;
	int		size;
	int		x;
	
	x = 0;
	size = ft_len_envp(envp);
	newenvp = (char **)malloc(sizeof(char *) * (size + 2));
	if (!newenvp)
		return (NULL);
	while (envp[x] != NULL)
	{
		newenvp[x] = ft_strdup(envp[x]);
		x++;
	}
	newenvp[x] = ft_strdup(str);
	newenvp[x + 1] = NULL;
	free(envp);
	envp = newenvp;
	ft_order_envp(envp);
	return (envp);
}

char	**ft_repacle_var_envp(char **envp, char *key, char *keyandvalue) // REEMPLAZA UNA VARIABLE EXISTENTE A ENVP
{
	int		x;
	
	x = 0;
	while (envp[x] != NULL)
	{
		if (ft_strncmp(key, ft_get_key(envp[x]), ft_strlen(key)) == 0)
		{
			envp[x] = keyandvalue;
		}
		x++;
	}
	return (envp);
}

char	*ft_get_keyandvalue(char *str, char *key)
{
	char	*value;
	
	if (ft_has_quote(str) == 1) // VERIFICO SI TIENE COMILLAS
	{
		value = ft_get_value(str);
	}
	else
	{
		value = ft_get_value_without_quotes(str);
	}
	
	if (value == NULL) // SI NO HAY VALUE
	{
		value = "=\"\"";
	}
	else
		value = ft_strjoin("=", value); // AGREGO '=' A value
	return (ft_strjoin(key,value));
}

char	**ft_export_with_var(char **envp, char *str) // EXPORT CON VARIABLE
{
	char	*keyandvalue;
	char	*key;
	int		is_in_envp;

	key = ft_get_key(str);
	is_in_envp = ft_is_in_envp(envp, key); // VERIFICO SI 'key' ESTA EN ENVP
	keyandvalue = ft_get_keyandvalue(str, key);

	if (is_in_envp == 1) 
	{
		envp = ft_repacle_var_envp(envp, key, keyandvalue);
	}
	else
	{
		envp = ft_add_var_envp(envp, keyandvalue);
	}
	return (envp);
}

void	ft_export(char **envp) //FUNCION PARA "env" Y "export" SIN OPCIONES O ARGUMENTOS
{
	int	x;

	x = 0;
	while (envp[x] != NULL)
	{
		// printf("declare -x "); // SE DESCOMENTA PARA VER EXACTAMENTE IGUAL A BASH
		printf("%s\n", envp[x]);
		x++;
	}
}


/*

🤖 Minishell ➤ export COLORTERM
COLORTERM="ll"
SI ESTAAAAAA

ERROR = LO EXPORTE SIN VALOR, Y AUN ASI APARECE "ll"



test=primercaso				== test="primercaso"
test=segundo caso			== test="segundo"
test="tercer caso"			== test="tercer caso"
test						== test=""
test=						== test=""

*/