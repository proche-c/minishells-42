SRCS = ./src/minishell.c\
		./src/parse/entry.c\
		./src/parse/utils.c\
		./src/parse/separate.c\
		./src/parse/string.c\
		./src/errors.c\
		./src/parse/data.c\
		./src/parse/parse.c\
		./src/parse/pipes_error.c\
		./libft/ft_split.c\
		./libft/ft_strlen.c\
		./libft/ft_strnstr.c\
		./libft/ft_strncmp.c\
		./libft/ft_strjoin.c\
		./libft/ft_strlcpy.c\
		./libft/ft_strdup.c\
		./libft/ft_substr.c\
		./src/lists.c\
		./src/signals.c\
		./src/builtins/envp.c\
		./src/builtins/export.c \
		./src/builtins/pwd.c \
		./src/libft.c \
		./src/builtins/unset.c \
		./src/builtins/cd.c \
		./src/builtins/echo.c \
		./src/builtins/utils_envp.c\
		./src/execute/execute.c\

OBJS = $(SRCS:.c=.o)

LDFLAGS	= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS = -I/Users/$(USER)/.brew/opt/readline/include

NAME = minishell

HEADER = ./include/minishell.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)

.c.o: ${CC} ${CFLAGS} -I $(HEADER) -c $< -o ${<:.c=.o}



$(NAME): $(OBJS) $(HEADER)
	$(CC) $(SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(NAME) -lreadline

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCS)

test: all
	./minishell