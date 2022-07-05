SRCS = ./src/minishell.c\
		./src/entry.c\
		./src/utils.c\
		./src/separate.c\
		./src/string.c\
		./src/errors.c\
		./src/data.c\
		./src/parse.c\
		./src/pipes_error.c\
		./libft/ft_split.c\
		./libft/ft_strlen.c\
		./libft/ft_strnstr.c\
		./libft/ft_strncmp.c\
		./libft/ft_strjoin.c\
		./libft/ft_strlcpy.c\
		./libft/ft_strdup.c\

OBJS = $(SRCS:.c=.o)

NAME = minishell

HEADER = ./include/minishell.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

.c.o: ${CC} ${CFLAGS} -I $(HEADER) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(SRCS) -o $(NAME) -lreadline

bonus: $(OBJS_BONUS) $(HEADER)
	$(CC) $(SRCS_BONUS) -o checker

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCS)

test: all