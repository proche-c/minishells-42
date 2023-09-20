/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:08:51 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_start(t_master *master, int argc, char **argv, char **envp)
{
	char	*aux;

	ft_signals();
	ft_create_envp(master, envp);
	ft_unset(master, master->envp, "OLDPWD");
	master->pwdflag = 0;
	// master->vuns = NULL;
	// master->initial_vuns = NULL;
	// master->vuns->first = 0;
	if (ft_is_in_envp(master->envp, "HOME"))
	{
		master->home = ft_strdup(ft_get_value_envp(master, "HOME"));
	}
	else if (ft_is_in_envp(master->envp, "USER"))
	{
		aux = ft_get_value_envp(master, "USER");
		master->home = ft_strjoin("/Users/", aux);
		free(aux);
	}
	else
		master->home = NULL;
	master->test_mode = TRUE;
	if (master->test_mode == TRUE)
		ft_test_mode(master, argc, argv);
	master->list = NULL;
	master->str = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_master	master;
	char		*str;

	ft_start(&master, argc, argv, envp);
	if (DEBUG == TRUE)
		ft_cd(&master, "./tests");
	while (argc && argv && envp)
	{
		if (DEBUG == TRUE)
			str = readline(ANSI_COLOR_SHELL"🤖 Minishell["RED"DEBUG"RESET"] ➤ "ANSI_COLOR_RESET);
		else
			str = readline(ANSI_COLOR_SHELL"🤖 Minishell ➤ "ANSI_COLOR_RESET);
		if (!str)
		{
			if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
			//ft_free_str(str); // Libero str y salgo (exit)
			//ft_free_vuns_all(master);
			exit (g_returnvalue);
		}
		else if (ft_strncmp(str, "1", 2) == 0)
			ft_parse_exec(&master, "export TMPENVVAR");
		else if (ft_strncmp(str, "2", 2) == 0)
			ft_parse_exec(&master, "$TMPENVVAR");
		else
		{
			add_history(str);
			ft_parse_exec(&master, str);
			ft_clean_master_middle(&master);
		}
	}
	return (0);
}
