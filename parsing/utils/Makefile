SRC = ft_strlen.c ft_calloc.c ft_striteri.c ft_strmapi.c ft_itoa.c ft_split.c \
		 ft_strtrim.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_memmove.c \
		 ft_memcpy.c ft_strlcpy.c ft_strlcat.c ft_isalpha.c ft_isdigit.c \
		 ft_isalnum.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c \
		 ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		 ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_strdup.c 
OBJS = ${SRC:.c=.o}
LIBC = ar -rcs
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f
NAME = libft.a


%.o: %.c libft.h
	$(CC) $(CFLAGS) -c -o $@ $<

${NAME}: ${OBJS}
		${LIBC} ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} $(OBJS)

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: clean