# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzuloaga <mzuloaga@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/30 10:18:48 by mzuloaga          #+#    #+#              #
#    Updated: 2024/01/30 16:57:34 by mzuloaga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =	cc
CFLAGS =	-Wall -Werror -Wextra
NAME =	libft.a

#Variable holding all .c files (minus bonus ones)
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
ft_strlen.c ft_bzero.c ft_memset.c ft_memcpy.c ft_memmove.c \
ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_get_next_line.c \

OBJS = $(SRCS:.c=.o)

# Bonus files
BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

#create libft.a (regular sources)
all:	$(NAME)
$(NAME):	$(OBJS)
	ar rcs $(NAME) $^

# Build the bonus part and add it to the library
bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $^

#remove .o files
clean:
	rm -f $(OBJS) $(BONUS_OBJS)

#remove .o files + library
fclean:	clean
	rm -f $(NAME)

#rebuild everything from scratch, compleely fresh start
re:	fclean all

.PHONY: all clean fclean re bonus
