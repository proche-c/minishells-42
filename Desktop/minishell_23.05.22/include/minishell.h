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
	char	**cmd;
	t_file 	*file_in;
	t_file 	*file_out;
	int 	pipes;
}	t_data;

typedef struct s_entry
{
	t_data	*data;
	struct s_entry	*next;
}	t_entry;

void 	ft_get_entry(char *str);
t_entry	*ft_get_first_entry(char **cmd, int num_elem, t_entry *first);
void ft_get_entries(t_entry *entry, int num_elem, char **cmds);
t_entry	*ft_get_new_entry(t_entry *entry, char **cmds, int i);
t_data 	*ft_get_data(t_data *data, char *line, t_entry *first, t_entry *entry);
int 	ft_get_num_pipes(char *str);
char	*ft_check_str(char *str);
int		ft_find_char(char *str, char c);
int		ft_eval_pipes(char **cmds, char *str);
void	ft_error_1(char **cmds);
void	ft_error_2(t_entry *first, char **cmds);
void	ft_error_3(char **cmds, t_data *data, t_entry *entry, t_entry *first);
void	ft_error_4(t_data *data, t_entry *entry, t_entry *first);
void	ft_free_cmds(char **cmds);
int 	ft_eval_redir(char *sep);


/* VICTOR */

#endif