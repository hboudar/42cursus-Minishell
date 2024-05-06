SRC		= execution.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c utils_builtins.c 
OBJ		= $(SRC:.c=.o)
HEADER	= execution.h
NAME	= execution
LIBC	=	ar -rcsLIBC	=	ar -rcs
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

all: pre $(NAME)

$(NAME): $(OBJ) utils/libft.a
	$(LIBC) $(OBJ) -o $(NAME) utils/libft.a

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
