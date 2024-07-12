SRC		=	minishell.c parsing/expand_utils2.c parsing/prompt_utils.c parsing/token_utils.c parsing/token_utils3.c parsing/wildcard.c \
			parsing/tools.c parsing/env.c parsing/token_type.c parsing/expand.c parsing/parse_cmd.c parsing/data_expand_utils.c \
			parsing/token_type2.c parsing/tokenize.c parsing/parse_prompt.c parsing/signals.c parsing/free_functions.c \
			parsing/redirections.c parsing/redirect_utils.c parsing/parse_pipes.c parsing/expand_utils.c \
			parsing/parse_token.c parsing/syntaxe_error.c parsing/token_utils2.c parsing/expand_here_doc.c \
			execution/execution.c execution/cmd/ft_env.c execution/cmd/ft_exit.c execution/cmd/ft_export.c execution/cmd/ft_pwd.c \
			execution/cmd/ft_export2.c execution/cmd/ft_unset.c execution/cmd/ft_cd.c execution/cmd/ft_echo.c execution/cmd/none_builtin.c \
			execution/utils/env_to_envp.c execution/utils/find_path.c execution/utils/signals.c \
			execution/cmd/here_doc.c execution/cmds/ft_pipe.c execution/cmd/redirection.c execution/utils/builtin.c execution/cmds/subshell.c \
			execution/cmd/none_redirection.c execution/utils/pid_addback.c

OBJ		= $(SRC:.c=.o)
HEADER	= minishell.h
NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
LIBFT	= utils/libft.a

READLINE_LIB = $(shell brew --prefix readline)/lib
READLINE_INCLUDES = $(shell brew --prefix readline)/include

all: pre $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) -lreadline $(CFLAGS) -L $(READLINE_LIB) -o $(NAME) $(LIBFT)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(READLINE_INCLUDES)

pre:
	$(MAKE) -C utils

clean:
	$(RM) $(OBJ)
	@cd utils && make clean

fclean: clean
	$(RM) $(NAME)
	@cd utils && make fclean

re: fclean all

.PHONY: clean re
