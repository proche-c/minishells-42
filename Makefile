SRCS = ${LIBFT} ${PRINT} ${BUILTINS} ${DEBUG} ${EXECUTE} ${PARSE} ${UTILS} ${LISTS} ${CLEAN} ${MAIN}

LIBFT = ./libft/ft_split.c \
	./libft/ft_strlen.c \
	./libft/ft_strnstr.c \
	./libft/ft_strncmp.c \
	./libft/ft_strjoin.c \
	./libft/ft_strlcpy.c \
	./libft/ft_strdup.c \
	./libft/ft_substr.c \
	./libft/ft_strtrim.c \
	./libft/ft_putstr_fd.c \
	./libft/ft_itoa.c \
	./libft/ft_atoi.c \
	./libft/ft_isdigit.c \
	./libft/ft_strrchr.c \
	
PRINT = ./src/print/src/ft_printf.c \
	./src/print/src/ft_utils_base.c \
	./src/print/src/ft_utils.c\

BUILTINS = ./src/builtins/cd_error.c \
	./src/builtins/cd.c \
	./src/builtins/cd_utils.c \
	./src/builtins/echo.c \
	./src/builtins/env_utils.c \
	./src/builtins/env.c \
	./src/builtins/envp_utils.c \
	./src/builtins/envp.c \
	./src/builtins/exit_utils.c \
	./src/builtins/exit.c \
	./src/builtins/export_utils.c \
	./src/builtins/export.c \
	./src/builtins/pwd.c \
	./src/builtins/unset.c \

DEBUG = ./src/debug/debug.c \

EXECUTE = ./src/execute/cmd.c \
	./src/execute/cmd_1.c \
	./src/execute/cmd_2.c \
	./src/execute/cmd_3.c \
	./src/execute/exec_builts.c \
	./src/execute/execute.c \
	./src/execute/pipes.c \
	./src/execute/pre_execute.c \
	./src/execute/redirection_input_simple.c \
	./src/execute/redirections.c \
	./src/execute/utils_execute.c \

PARSE = ./src/parse/check_str.c \
	./src/parse/utils_quotes.c \
	./src/parse/check_pipes.c \
	./src/parse/check_redir.c \
	./src/parse/check_d_redir.c \
	./src/parse/double_redir.c \
	./src/parse/data.c \
	./src/parse/commands.c \
	./src/parse/entry.c \
	./src/parse/parse.c \
	./src/parse/path.c \
	./src/parse/replace_var.c \
	./src/parse/separate.c \
	./src/parse/separate_cmd.c \
	./src/parse/utils_separate_cmd.c \
	./src/parse/utils_parse.c \
	./src/parse/quotes.c \
	./src/parse/dollar.c \
	./src/parse/utils_dollar.c \
	./src/parse/replace.c \
	./src/parse/replace_tilde.c \
	./src/parse/utils_tilde.c \
	./src/parse/utils_replace.c \

UTILS =	./src/utils/compare_str.c \
	./src/utils/errors.c \
	./src/utils/ft_strjoin_3.c \
	./src/utils/home.c \
	./src/utils/put_str.c \
	./src/utils/returns.c \
	./src/utils/test_mode.c \

LISTS = ./src/lists/parse.c \
	./src/lists/lists.c \
	./src/lists/envp.c \
	./src/lists/redir.c \
	./src/lists/files.c \
	./src/lists/args.c \
	./src/lists/casew.c \

CLEAN = ./src/clean/clean.c \
	./src/clean/clean_lists.c \
	./src/clean/clean_parse.c \

MAIN = ./src/minishell.c \
	./src/signals.c \

OBJS = $(SRCS:.c=.o)

NAME = minishell

HEADER = ./include/minishell.h

CC = gcc

# -I readline FUNCIONA EN 42 PORQUE YA ESTA INSTALADO POR DEFECTO EN TODOS LOS MACS
#CFLAGS		= -Wall -Wextra -Werror -g $(INC) -I readline

#CFLAGS		= -Wall -Wextra -Werror -g $(INC) -I readline
#CFLAGS		= -Wall -Wextra -Werror -g $(INC) -I ~/.brew/opt/readline/include #Esta compilacion funciona en 42 para readline # SF en 42
CFLAGS		= -Wall -Wextra -Werror -g $(INC) -I /opt/homebrew/opt/readline/include #Esta compilacion funciona en m2 para readline

INCS        = -I ./include/

RM = rm -f

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(NAME): $(OBJS) $(HEADER)
#	@$(CC) $(CFLAGS) $(OBJS) -lreadline -L readline
#	@$(CC) $(CFLAGS) $(OBJS) -lreadline -L ~/.brew/opt/readline/lib -o $(NAME)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -L /opt/homebrew/opt/readline/lib -o $(NAME)
	@echo "\x1b[32mAll compiled\x1b[0m"

clean:
	@$(RM) $(OBJS)
	@echo "\x1b[31mObjs removed\x1b[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\x1b[31mProgram removed\x1b[0m"

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCS)

test: clean re
	@$(RM) $(OBJS)
	@./minishell

leaks: all
	@clear
	@leaks -quiet -atExit -- ./minishell

debug:
	@$(CC) -D DEBUG=TRUE $(CFLAGS) $(OBJS) -lreadline -L /opt/homebrew/opt/readline/lib -o $(NAME)