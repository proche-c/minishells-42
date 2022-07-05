/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:49:58 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cc(int num)
{
	printf("CONTROL + C, %i\n", num);
	return ;
}

void	ft_cr(int num)
{
	printf("CONTROL + \\, %i\n", num);
}

void	ft_signals(void)
{
	signal(SIGINT, &ft_cc);
	signal (SIGQUIT, &ft_cr);
}

int	main(int argc, char **argv, char **envp)
{
	char *str;
	//char	*prog_path = "/bin/ls";
	//char *const args[] = {"ls", "-la","/bin", 0};

	//execve(prog_path, args, envp);
	ft_signals();
	while (argc && argv && envp)
	{
		str = readline(ANSI_COLOR_SHELL"🤖 Minishell ➤ "ANSI_COLOR_RESET);
		if (str == NULL)
		{
			free(str);
   			exit(0);
		}
		// ft_parse_exec(str);
		ft_parse_exec("ls -la 3er | wc eeee");
	}

	return(0);
}
