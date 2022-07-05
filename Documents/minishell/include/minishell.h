/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/06/15 19:57:08 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <unistd.h> //getcwd
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

int g_returnvalue;


/* PAULA */

typedef struct s_down //Comandos->Down
{
	char	*arg;
	struct s_down	*next;
}	t_down;

typedef struct s_data //Lista de Comandos // MUERTE
{
	int 	type;
	int		num_args;
	char	*cmd;
	int 	cmd_type;
	char	**args;
	t_down *down;
	struct s_data	*next;
}	t_data;

typedef struct s_envp
{
	int		type; // 1 = (pepe="xd") || 2 = (pepe=) || 3 = (pepe)
	char	*key;
	char	*value;
	struct s_envp *next;
}	t_envp;


typedef struct s_master //Estructura master
{
	struct s_data	*list; // Lista de comandos
	struct s_envp	*envp; // Lista de variables de entorno
	char	*str; 			// Str original
	char	**elem;			// Resultado del split raro
	int		num_elem;		// Numero de elementos (incluidos pipes)
	int		error;			// Error ?
	char 	**bin_paths;	//path donde se encuantran las funciones de bin
}	t_master;

//parse

void	ft_value_master(t_master *master, char *str); // Agregado por victor
void	ft_parse_exec(t_master *master, char *str, char **envp);

//string

void	ft_check_quote(t_master *master);
void	ft_check_str(t_master *master);
int 	ft_find_quote(char *str, char c);

//pipes_error

int 	ft_eval_pipes(char *str);

//utils

int 	ft_get_num_elem(char *str);
int 	ft_char_resv(char *str, int i);

//errors
void 	ft_error_1(char *str);
void 	ft_error_2(char **elem);
void	ft_error_3(char **elem, t_data *data, char **cmds);
void	ft_error_4(char **elem, t_data *data, char **cmds);
void	ft_error_5(char **elem, t_data *data, char **cmds);

//separate

void	ft_separate_str(t_master *master);

//entry
void	ft_get_entry(t_master *master);
void	ft_get_value_list(t_master *master);
void	ft_get_first_elem(t_master *master);
void	ft_get_new_entry(t_data *temp, char **elem, int i);
t_data *ft_get_all_entry(char **elem, t_data *first);

//data

t_data	*ft_get_data(t_master *master, t_data *new_data, int j);

//execute

void	ft_get_paths(t_master *master);
int	ft_execute_cmd(t_master *master, char **envp);





/* VICTOR */

/* SIGNALS */
void	ft_signals(void);
void	ft_cr(int num);
void	ft_cc(int num);
char	*ft_pwd(void);



/* LIBFT */
int		ft_countwords(const char *s, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/* ECHO */
void	ft_echo(t_data *data);

/* CD */
void	ft_cd(char *dir);

/* EXPORT */
void	ft_export(t_envp *envp);
void	ft_export_with_var(t_master *master);
void	ft_order_envp(char **envp);
int		ft_len_envp(char **envp);
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
char	*ft_get_value_without_quotes(char *str);
int		ft_has_quote(char *str);
int		ft_is_in_envp(t_envp *envp, char *str);

/* ENV */
void	ft_env(t_envp *envp);

/* UNSET */
char	*ft_search(char *str);
char	**ft_unset(char **envp, char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// Listas
t_data	*ft_new_cmd(void);
t_down	*ft_down_new(char *str);
t_envp	*ft_new_envp(char *key, char *value);
t_envp	*ft_lst_last(t_envp *list);

// Signals
void	ft_cc(int num);
void	ft_cr(int num);
void	ft_signals(void);

// Envp
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
int		ft_len_envp(char **envp);
void	ft_order_envp(char **envp);
char	**ft_create_new_envp_char(char **envp);
void	ft_create_envp(t_master *master, char **envp);

/* EXEC BUILTS */
void	ft_exec_builts(t_master *master);

#endif