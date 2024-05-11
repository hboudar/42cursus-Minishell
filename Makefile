SRC		=	minishell.c parsing/parsing.c parsing/prompt_utils.c parsing/token_utils.c \
			parsing/tools.c parsing/env.c parsing/token_type.c \
			parsing/token_type2.c parsing/tokenize.c parsing/parse_prompt.c \
			parsing/.print.c parsing/parse_token.c parsing/syntaxe_error.c parsing/token_utils2.c \
<<<<<<< HEAD
			execution/execution.c execution/cmd/no_cmd.c execution/cmd/ft_env.c execution/cmd/ft_exit.c \
			execution/cmd/ft_export.c execution/cmd/ft_pwd.c execution/cmd/ft_unset.c execution/cmd/ft_cd.c \
			execution/cmd/ft_echo.c execution/cmd/non_builtin.c execution/cmd/utils_builtins.c execution/utils/env_to_envp.c \
			execution/utils/find_path.c
=======
			execution/execution.c execution/cmd/ft_env.c execution/cmd/ft_exit.c execution/cmd/ft_export.c execution/cmd/ft_pwd.c \
			execution/cmd/ft_unset.c execution/cmd/ft_cd.c execution/cmd/ft_echo.c execution/cmd/non_builtin.c \
			execution/cmd/utils_builtins.c execution/cmd/no_cmd.c execution/utils/env_to_envp.c execution/utils/find_path.c
>>>>>>> 5a45e5728222da18769288f2905a17078636596a
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
