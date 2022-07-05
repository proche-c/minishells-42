/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/09 19:10:27 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <unistd.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> // SEÑALES
# include <stdlib.h> // EXIT
# include "../libft/libft.h"
# define ANSI_COLOR_SHELL     "\x1b[96m" // COLOR DE SHELL
# define ANSI_COLOR_RESET   "\x1b[0m" // COLOR POR DEFECTO
# define PIPE 1
# define FILE_OUT 2
# define FILE_IN 3
# define DFILE_OUT 4
# define DFILE_IN 5


/* PAULA */

typedef struct s_file
{
	char **name;
	int *fd_in;
	int *fd_out;
	int *double_r;
}	t_file;

typedef struct s_data
{
	int 	type;
	char	*cmd;
	char 	**args;
}	t_data;

typedef struct s_entry
{
	t_data	*data;
	struct s_entry	*next;
}	t_entry;

//parse

void	ft_parse_exec(char *str);

//string

char 	*ft_check_quote(char *str);
char 	*ft_check_str(char *str);
int 	ft_find_quote(char *str, char c);

//pipes_error

int 	ft_eval_pipes(char *str);

//utils

int 	ft_get_num_elem(char *str);
int 	ft_char_resv(char *str, int i);
int 	ft_get_elem(char **elem);

//errors
void 	ft_error_1(char *str);
void 	ft_error_2(char **elem);
void	ft_error_3(char **elem, t_data *data, char **cmds);
void	ft_error_4(char **elem, t_data *data, char **cmds);
void	ft_error_5(char **elem, t_data *data, char **cmds);

//separate

char	**ft_separate_str(char *str);

//entry

t_entry	*ft_get_entry(char *str, t_entry *first);
t_entry	*ft_get_first_elem(char **elem, t_entry *first);
void	ft_get_new_entry(t_entry *temp, char **elem, int i);
t_entry *ft_get_all_entry(char **elem, t_entry *first);

//data

t_data 	*ft_get_data(t_data *data, char **elem, int j);
t_data *ft_initialize_data(t_data *data);




/* VICTOR */

#endif