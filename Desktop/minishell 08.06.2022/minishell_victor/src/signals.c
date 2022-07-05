/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/25 12:09:30 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/*
FUNCIONA TODO EXEPTO BORRAR LO ESCRITO AL MOMENTO DE ENVIAR LA SEÑAL

NECESARIO PARA INSTALAR BREW
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update

INSTALAR READLINE
brew install readline

*/

void	ft_cc(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_cr(int num) //ESTA IMPECABLE
{
	(void)num;

	printf(ANSI_COLOR_SHELL"🤖 Minishell ➤ "ANSI_COLOR_RESET);
	
}

void	ft_signals(void)
{
	// write(1, "\b\b", 2);
	// printf("\t");
	signal(SIGINT, &ft_cc); //CONTROL + C
	signal (SIGQUIT, &ft_cr); //CONTROL + /
	//write(1, "12", 2);
}