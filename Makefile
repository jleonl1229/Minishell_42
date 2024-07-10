CC           = gcc
LIBFT_DIR    = minishell_libft/
LIBFT        = $(LIBFT_DIR)libft.a
CFLAGS       = -Wall -Wextra -Werror
MNISHELL_DIR = ./
HEADERS      = -I $(MINISHELL_DIR) -I $(LIBFT_DIR)
NAME         = minishell
RM           = rm -rf

CFILES = $(wildcard $(MNISHELL_DIR)*.c)
OFILES = $(CFILES:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) -L$(LIBFT_DIR) -lft -lm -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all
