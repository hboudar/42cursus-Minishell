SRC		=	ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_isword.c	 \
			ft_striteri.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_itoa.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c  \
			ft_strncmp.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c  \
			ft_strlcpy.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_is_whitespace.c

OBJS	=	${SRC:.c=.o}
LIBC	=	ar -rcs
CFLAGS	=	-Wall -Wextra -Werror
CC		=	cc
RM		=	rm -f
NAME	=	libft.a

all: ${NAME}

${NAME}: ${OBJS}
		${LIBC} ${NAME} ${OBJS}

%.o: %.c libft.h
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} $(OBJS)

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: clean fclean all bonus re
