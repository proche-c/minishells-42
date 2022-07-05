/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/09 13:16:24 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_envp *ft_find_path(t_master *master)
{
	t_envp *temp;
	char *p;
	int i;
	int res;

	printf("FT_FIND_PATH\n");
	p = "PATH";
	temp = master->envp;
	i = 0;
	while (temp->key)
	{
		res = ft_strncmp(p,temp->key, 5);
		if (res == 0)
		{
			printf ("SAY HELLO\n");
			return(temp);
		}
		printf("RES ES :%d\n", res);
		printf("env[%d]: %s %s\n",i, temp->key, temp->value);
		temp = temp->next;
		i++;
	}
	printf("FT_FIND_PATH2\n");
	return (temp);
}

void	ft_get_paths(t_master *master)
{
	char **bin_paths;
	t_envp *result;
	//char *paths;
	char *cmd;
	int i;

	printf("FT_GET_PATHS\n");
	//printf("PATH:%s\n", envp[12]);
	result = ft_find_path(master);
	printf("PATH:%s\n", result->value);
	bin_paths = ft_split(result->value, ':');
	bin_paths[0] = ft_substr((char const *)bin_paths[0], 5, 800);
	cmd = ft_strjoin("/", master->list->cmd);
	i = 0;
	while(bin_paths[i])
	{
		bin_paths[i] = ft_strjoin(bin_paths[i], cmd);
		printf("%s\n", bin_paths[i]);
		i++;
	}
	master->bin_paths = bin_paths;
}

void ft_get_args(t_master *master)
{
	//char **args;
	int i;

	i = 0;
	master->list->args = malloc(sizeof(char *) * 7);
	master->list->args[i] = ft_strdup(master->list->cmd);
	i++;
	while (master->list->down)
	{
		printf("PRE ASIGNACION arg[%d]:%s\n", i, master->list->down->arg);
		master->list->args[i] = ft_strdup(master->list->down->arg);
		printf("POST ASIGNACION arg[%d]:%s\n", i, master->list->args[i]);
		master->list->down = master->list->down->next;
		i++;
	}
	master->list->args[i] = 0;
	//return (args);
}

int	ft_execute_cmd(t_master *master, char **envp)
{
	g_returnvalue = 0;

	pid_t pid_ex;
	int i;

	ft_get_args(master);
	i = 0;
	while (master->bin_paths[i])
	{
		pid_ex = fork();
		if (pid_ex == 0)
		{
			//printf("he entrado en el bucle %d veces\n", i);
			g_returnvalue = execve(master->bin_paths[i], master->list->args, envp);
			printf("he entrado en el bucle %d veces y g_returnvalue es: %d\n", i, g_returnvalue);
			if (g_returnvalue == 0 || g_returnvalue == 1)
			{
				printf("el comando se ha ejecutado correctamente\n");
				exit(0);
			}
			//i++;
			else 
			{
				//printf("error\n");
				exit(0);
			}
		}
		i++;
	}
	printf("   G_returnvalue ES: %d\n", g_returnvalue);
	return(g_returnvalue);
}
