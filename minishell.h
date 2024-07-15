#include <unistd.h> //write, read, access, dup, dup2, execve, fork, pipe, unlink
#include <sys/wait.h> //wait, waitpid
#include <fcntl.h> //open, close
#include <stdlib.h> // malloc, free 
#include <stdio.h> // perror
#include <errno.h>
#include "./minishell_libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


/*struct of a node in a linked list. Each node's data made of env var name + content 
Essentially a copy of char **env, likely done to easily manipulate env vars by our program
*/
typedef struct s_env
{
    char			*env_name;
    char			*env_value;
	struct s_env	*next;
}	t_env;

/*mother of all structs, to be completed as we advance on project
*/
typedef struct s_sh_data
{
    t_env   *env_header; // pointer to the head of the linked list holding the env vars
    char    *prev_line; //last line saved to history
}   t_sh_data;



//shell_init/shell_init.c
t_env *dup_env(char **envp);
void shell_init(t_sh_data *sh, char **envp);

//shell_loop/shell_loop.c
void save_to_history(t_sh_data *sh, char *line);
char    *get_input(char *line);
void shell_loop(t_sh_data *sh);

//shell_loop/input_validation.c


//minishell.c
void env_checker(char **envp);
void	argc_checker(int argc);

//env_utils.c
t_env	*env_create_node(char *var_name, char *var_content);
void	env_add_node(t_env **header, t_env *new_node);

//input_utils.c
int	bad_initial_char(char *line);
int	bad_final_char(char *line);
int is_open_quotes(char *line);
int	is_space(char *line);

//input_utils2.c
void skip_spaces(char *str, int *index);
void skip_quotes(char *str, int *index);
int	space_and_chars(char *line);

