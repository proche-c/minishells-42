/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2022/05/31 13:58:17 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# include <stdio.h>
# include <unistd.h> //getcwd
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> // SEÑALES
# include <stdlib.h> // EXIT, getenv
# define ANSI_COLOR_SHELL     "\x1b[96m" // COLOR DE SHELL
# define ANSI_COLOR_RESET   "\x1b[0m" // COLOR POR DEFECTO


/* PAULA */











/* VICTOR */

/* SIGNALS */
void	ft_signals(void);
void	ft_cr(int num);
void	ft_cc(int num);

char	*ft_var(char *str);
void	ft_export(char **envp);
char	*ft_pwd(void);



/* LIBFT */
int		ft_countwords(const char *s, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

/* ECHO */
void	ft_echo(char *str);

/* CD */
void	ft_cd(char *dir);

/* EXPORT / ENVP */
char	**ft_export_with_var(char **envp, char *str);
void	ft_order_envp(char **envp);
int		ft_len_envp(char **envp);
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
char	*ft_get_value_without_quotes(char *str);
int		ft_has_quote(char *str);
int		ft_is_in_envp(char **envp, char *str);


/* UNSET */
char	*ft_search(char *str);
char	**ft_unset(char **envp, char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//void	rl_replace_line (const char *text, int clear_undo);

#endif