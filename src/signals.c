/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/08/20 23:09:04 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
FUNCIONA TODO EXCEPTO BORRAR LO ESCRITO AL MOMENTO DE ENVIAR LA SEÑAL

NECESARIO PARA INSTALAR BREW
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update

INSTALAR READLINE
brew install readline

*/

void	ft_cc(int num)
{
	printa("ENTRO EN FT_CC");
	(void)num;
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_returnvalue = 1;
}

void	ft_cr(int num) //ESTA IMPECABLE
{
	printa("ENTRO EN FT_CR");
	(void)num;
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signals(void)
{
	struct termios	termios;

	if (tcgetattr(STDIN_FILENO, &termios) == -1)
		return ;
	termios.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios) == -1)
		return ;
	signal(SIGINT, &ft_cc); //CONTROL + C
	signal (SIGQUIT, &ft_cr); //CONTROL + /
}

