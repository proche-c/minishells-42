/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 20:15:13 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_var_envp(t_envp *envp, char *str) // AGREGA UNA NUEVA VARIABLE A ENVP
{
	t_envp	*newenvp;
	t_envp	*last;

	newenvp = ft_new_envp(ft_get_key(str), ft_get_value(str));
	newenvp->type = 4;
	last = ft_lst_last(envp);
	last->next = newenvp;
	
	printf("LLAVE AGREDADA == (%s=%s)\n", newenvp->key, newenvp->value);

}

void	ft_repacle_var_envp(t_envp *envp, char *key, char *keyandvalue) // REEMPLAZA UNA VARIABLE EXISTENTE A ENVP
{
	while (envp != NULL)
	{
		if (ft_strncmp(key, ft_get_key(envp->key), ft_strlen(key)) == 0)
		{
			//envp[x] = keyandvalue;
			envp->key = ft_strdup(key);
			envp->key = ft_get_value(keyandvalue);
		}
		envp = envp->next;
	}
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

void	ft_export_with_var(t_master *master) // EXPORT CON VARIABLE
{
	char	*keyandvalue;
	char	*key;
	int		is_in_envp;

	key = ft_get_key(master->str);
	is_in_envp = ft_is_in_envp(master->envp, key); // VERIFICO SI 'key' ESTA EN ENVP
	keyandvalue = ft_get_keyandvalue(master->str, key); // Modifico el string y le doy un valor valido

	printf("FT_EXPORT_WITH_VAR\n");
	printf("KEYANDVALUE == (%s)\n", keyandvalue);
	if (is_in_envp == 1) //Si estoy reemplazando una variable
	{
		ft_repacle_var_envp(master->envp, key, keyandvalue);
	}
	else
	{
		ft_add_var_envp(master->envp, keyandvalue);
	}
	printf("END\n");
}

void	ft_export(t_envp *envp) //FUNCION PARA "env" Y "export" SIN OPCIONES O ARGUMENTOS
{
	while (envp != NULL)
	{
		printf("declare -x "); // SE DESCOMENTA PARA VER EXACTAMENTE IGUAL A BASH
		if (envp->type == 1) // 1 = (pepe="xd") || 2 = (pepe=) || 3 = (pepe)
		{
			printf("%s=%s\n", envp->key, envp->value);
		}
		else if (envp->type == 2)
		{
			printf("%s=\n", envp->key);
		}
		else if (envp->type == 3) 
		{
			printf("%s=""\n", envp->key);
		}
		else if (envp->type == 4)
		{
			printf("AGREGADO = KEY == (%s), VALUE == (%s)\n", envp->key, envp->value);
		}
		envp = envp->next;
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