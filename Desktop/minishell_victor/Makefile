SRCS = ./src/minishell.c \
	./src/signals.c \
	./src/var.c \
	./src/export.c \
	./src/pwd.c \
	./src/libft.c \
	./src/unset.c \
	./src/cd.c \
	./src/echo.c \
	./src/utils_envp.c

OBJS = $(SRCS:.c=.o)

LDFLAGS	= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS = -I/Users/$(USER)/.brew/opt/readline/include

NAME = minishell

HEADER = ./include/minishell.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

.c.o: ${CC} ${CFLAGS} -I $(HEADER) -c $< -o ${<:.c=.o}

all: $(NAME)

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