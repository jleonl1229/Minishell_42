CC           = gcc
LIBFT_DIR    = minishell_libft/
LIBFT        = $(LIBFT_DIR)libft.a
CFLAGS       = -Wall -Wextra -Werror
MINISHELL_DIR = ./
SHELL_INIT_DIR = shell_init/
SHELL_LOOP_DIR = shell_loop/
UTILS_DIR    = utils/
PARSING_DIR = parsing/
ERRORS_FREES = errors_frees/
EXECUTION_DIR = execution/
SIGNALS_DIR = signals/
BUILTINS_DIR = built_ins/
HEADERS      = -I $(MINISHELL_DIR) -I $(LIBFT_DIR)
NAME         = minishell
RM           = rm -rf

CFILES = $(wildcard $(MINISHELL_DIR)*.c) \
         $(wildcard $(SHELL_INIT_DIR)*.c) \
         $(wildcard $(SHELL_LOOP_DIR)*.c) \
         $(wildcard $(UTILS_DIR)*.c) \
		 $(wildcard $(PARSING_DIR)*.c)\
		 $(wildcard $(ERRORS_FREES)*.c)\
		 $(wildcard $(EXECUTION_DIR)*.c)\
		 $(wildcard $(SIGNALS_DIR)*.c)\
		 $(wildcard $(BUILTINS_DIR)*.c)\

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
