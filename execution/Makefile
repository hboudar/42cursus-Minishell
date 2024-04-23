SRC		= execution.c
OBJ		= $(SRC:.c=.o)
HEADER	= execution.h
NAME	= exe
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all: pre $(NAME)

$(NAME): $(OBJ) utils/libft.a
	$(CC) $(OBJ) -o $(NAME) utils/libft.a

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
