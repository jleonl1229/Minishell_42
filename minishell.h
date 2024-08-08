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

/* structure of a node with data about a pipe segment
example: echo "hello" > out | cat out", there are 2 t_parsed_data nodes
*/
typedef struct s_parsed_data
{
    char *path; //absolute path to executable
    char *cmd; //executable command, without args
    char **args; //command args
    int     simple_in_redir; //fd where stdin is redirected from
    int     simple_out_redir; //fd where stdout is redirected to
    t_list *here_doc; //delimiter to handle here_doc feature
    int     append; //filename to handle append redirection to stdout
    struct s_parsed_data *next;
} t_parsed_data;

/*mother of all structs, to be completed as we advance on project
*/
typedef struct s_sh_data
{
    t_env   *env_header; // pointer to the head of the linked list holding the env vars
    char    *prev_line; //last line saved to history
    char *new_line; //user inputed command with spaces around special chars
    t_parsed_data *parsed_header; //pointer to the head of the linked list holding the pipe segments data
}   t_sh_data;

//parsing/parsing.c
char **split_by_pipe(char *line, int start, int segment_index, int i);
void parse_line(t_sh_data **sh, t_parsed_data **header, char **split_space, char **pipe_segments);
t_parsed_data *parsing(t_sh_data *sh);

//parsing/env_parsing.c
char	*expanded_var (char **env_pair, char *input, int *start);
char **get_var_content(char *input, int start, t_env *head);
char *act_on_dollar(char *input, int *j, t_env *env_list);
char  **env_parse (int single_q, int double_q, char **input, t_env *env_list );

//shell_init/shell_init.c
t_env *dup_env(char **envp, t_env *header, t_sh_data **sh);
void shell_init(t_sh_data **sh, char **envp);

//shell_loop/shell_loop.c
int append_line(t_sh_data *sh, char *line);
int save_to_history(t_sh_data *sh, char *line, int e_pipe);
int get_input(t_sh_data *sh, char *line, int e_pipe);
void shell_loop(t_sh_data **sh);

//shell_loop/input_validation.c
char three_invalid_print(char *line, char *last_invalid);
int three_valid(char *line);
int input_validation(char *line, t_sh_data **sh);

//minishell.c
void env_checker(char **envp, t_sh_data **sh);
void	argc_checker(int argc, t_sh_data **sh);

//errors_frees/frees.c
char	**free_matrix(char **pointer);
void free_tlist(t_list *header);
void free_env_list(t_env *head);
void pre_parse_cleanup(t_sh_data **sh, t_env **header, char ***org);
void    free_parsing_list(t_sh_data **sh);
void parsing_cleanup(t_sh_data **sh, char **pipe_segments, char **split_space);

//utils/env_utils.c
t_env	*env_create_node(char *var_name, char *var_content);
void	env_add_node(t_env **header, t_env *new_node);
int env_quotes(char c, int *single_q, int *double_q, int *j);
char *find_env_pair(t_env *head, char *var_name);

//utils/input_utils.c
int	bad_initial_char(char *line, t_sh_data **sh);
int	bad_final_char(char *line, t_sh_data **sh);
int is_open_quotes(char *line);
int	is_space(char *line);
int invalid_sequence(char *line, int i, int count);

//utils/input_utils2.c
void skip_spaces(char *str, int *index);
void skip_quotes(char *str, int *index);
int	space_and_chars(char *line);
int sized2_invalid(char *line);
int valid_not_implemented(char *line);

//utils/parsing_utils.c
void	remove_quotes(char *element);
int count_segments(char *str);
size_t	count_substrings(const char *s, char c, int in_dquotes, int in_squotes);
size_t	count_char(const char *s, char c);
char	**ft_split_quotes(const char *s, char c);

//utils/parsing_utils2.c
int is_special_char(char c) ;
int new_line_length(char *line, int len, int in_dquote, int in_squote);
void fill_new_line(char **new_line, char *line, int in_squote, int in_dquote);
void add_space(t_sh_data *sh);

//utils/parsing_utils3.c
void parse_add_node(t_parsed_data **head, t_parsed_data *new_node);
char **alloc_cpy_segment(char **segment);
int mod_cpy_segment(char **cpy_segment, int i, t_parsed_data *parsed_data, char **segment);
int redir_fd(int *redir, char *file, char *redir_type);
int handle_redir(char *redir, char *file, t_parsed_data *parsed_data);
char **parse_redir(t_parsed_data *parsed_data, char **split_space);
char **cmd_arr(char **cpy_segment);
int fill_cmd_and_args(int i, int j, t_parsed_data *node, char **cmd);
char *path_is_exec(t_parsed_data *node, char **env_value );
char    **extract_path(t_sh_data *sh);
int fill_path(t_sh_data *sh, t_parsed_data *node);
int parse_cmd_and_path(t_sh_data *sh, t_parsed_data *node, char **segment, char **cpy_segment);
