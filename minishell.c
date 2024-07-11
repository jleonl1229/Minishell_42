
#include "minishell.h"

/*if PATH is null the shell can't execute non-built-in programs, 
    but should this check be made in a future step and here just check if env is null? Probably yes
    PATH can be deleted with this command: "unset PATH"
    envp can be null, and so no PATH be found
    env can be non null, but no PATH be found

*/
void env_checker(char **envp)
{
    int path_found;

    path_found = 0;
    if ( envp == NULL || *envp == NULL)
    {
        perror("No ENV found, don't delete ENVs!");
        exit(EXIT_SUCCESS);
    }
    while (*envp != NULL)
    {
        if (ft_strncmp(*envp, "PATH=", ft_strlen("PATH=")) == 0)
        {
            path_found = 1;
            break;
        }
        envp++;
    }
    if (path_found == 0)
    {
        perror("No PATH found, don't delete the PATH env!");
        exit(EXIT_SUCCESS);
    }
}

// exits program if argc is not 1
void	argc_checker(int argc)
{
    if (argc != 1)
    {
        perror("Invalid argument count. Usage: ./minishell");
        exit(EXIT_SUCCESS);
    }

}

int main(int argc, char **argv, char **envp)
{
    t_sh_data sh;

    printf("argv[0] is: %s\n", argv[0]); //to be replaced by (void)argv
    argc_checker(argc);
        //exit error if argc > 1
    env_checker(envp);
        //exit error if envp or *envp NULL
    printf("entering shell init...\n");
    shell_init(&sh, envp);
    shell_loop(&sh);
    return 0;
}