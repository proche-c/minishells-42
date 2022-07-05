SRCS = ./src/minishell.c\
		./src/data.c\
		./src/entry.c\
		./src/checkers.c\
		./src/utils.c\
		./libft/ft_split.c\
		./libft/ft_strlen.c\
		./libft/ft_strnstr.c\
		./libft/ft_strncmp.c\
		./src/errors.c\
		./libft/ft_strjoin.c\

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