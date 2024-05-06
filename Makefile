SRC		= minishell.c parsing/parsing.c parsing/prompt_utils.c parsing/token_utils.c \
			parsing/tools.c parsing/env.c parsing/token_type.c \
			parsing/token_type2.c parsing/tokenize.c parsing/parse_prompt.c \
			parsing/.print.c parsing/parse_token.c \
			execution/execution.c execution/builtins/ft_cd.c execution/builtins/ft_echo.c \
			execution/builtins/ft_env.c execution/builtins/ft_exit.c \ 
			execution/builtins/ft_export.c execution/builtins/ft_pwd.c execution/builtins/ft_unset.c \
			execution/builtins/utils_builtins.c execution/execution_utils.c \
OBJ		= $(SRC:.c=.o)
HEADER	= execution.h
NAME	= minishell
PARSING = parsing/parsing.a
EXECUTION = execution/execution.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
LIBFT	= parsing/utils/libft.a

all: pre $(NAME)

$(NAME): $(OBJ) $(PARSING) $(EXECUTION) $(LIBFT)
	$(CC) -lreadline $(OBJ) -o $(NAME) $(PARSING) $(EXECUTION) $(LIBFT)

%.o: %.c $(HEADER) $(PARSING) $(EXECUTION) $(LIBFT)
	$(CC) $(CFLAGS) -c $< -o $@

pre:
	@cd parsing && make
	@cd execution && make

clean:
	$(RM) $(OBJ) $(PARSING) $(EXECUTION)
	@cd parsing && make clean
	@cd execution && make clean

fclean: clean
	$(RM) $(NAME) $(PARSING) $(EXECUTION)
	@cd parsing && make fclean
	@cd execution && make fclean

re: fclean all

.PHONY: clean re
