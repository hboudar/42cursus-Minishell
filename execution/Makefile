SRC		=	execution.c \
			builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c \
			builtins/ft_exit.c builtins/ft_export.c builtins/ft_pwd.c \
			builtins/ft_unset.c builtins/utils_builtins.c

OBJ		=	$(SRC:.c=.o)
HEADER	=	execution.h
NAME	=	execution.a
LIBC	=	ar -rcs
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

RM		= rm -f

all: pre $(NAME)

$(NAME): $(OBJ) utils/libft.a
	$(LIBC) $(NAME) $(OBJ) utils/libft.a

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
