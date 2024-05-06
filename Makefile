SRC		= minishell.c parsing/parsing.c parsing/prompt_utils.c parsing/token_utils.c \
			parsing/tools.c parsing/env.c parsing/token_type.c \
			parsing/token_type2.c parsing/tokenize.c parsing/parse_prompt.c \
			parsing/.print.c parsing/parse_token.c \
			execution/execution.c execution/builtins/ft_cd.c execution/builtins/ft_echo.c \
			execution/builtins/ft_env.c execution/builtins/ft_exit.c \
			execution/builtins/ft_export.c execution/builtins/ft_pwd.c execution/builtins/ft_unset.c \
			execution/builtins/utils_builtins.c
OBJ		= $(SRC:.c=.o)
HEADER	= execution.h
NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
LIBFT	= utils/libft.a

all: pre $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -lreadline $(OBJ) -o $(NAME) $(LIBFT)

%.o: %.c $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

pre:
	@cd utils && make

clean:
	$(RM) $(OBJ)
	@cd utils && make clean

fclean: clean
	$(RM) $(NAME)
	@cd utils && make fclean

re: fclean all

.PHONY: clean re
