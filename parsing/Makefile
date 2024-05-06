SRC		= parsing.c prompt_utils.c token_utils.c ../minishell.c tools.c env.c token_type.c\
			token_type2.c tokenize.c parse_prompt.c .print.c parse_token.c
OBJ		= $(SRC:.c=.o)
HEADER	= parsing.h ../minishell.h
NAME	= parsing
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

all: pre $(NAME)

$(NAME): $(OBJ) utils/libft.a ../minishell.h
	$(CC) -lreadline $(OBJ) -o $(NAME) utils/libft.a

%.o: %.c $(HEADER)
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
