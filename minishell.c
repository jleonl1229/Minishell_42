
#include "minishell.h"

/*if PATH is null the shell can't execute non-built-in programs, 
    but should this check be made in a future step and here just check if env is null? Probably yes
    PATH can be deleted with this command: "unset PATH"
    envp can be null, and so no PATH be found
    env can be non null, but no PATH be found

*/
void env_checker(char **envp, t_sh_data **sh)
{
    int path_found;

    path_found = 0;
    if ( envp == NULL || *envp == NULL)
    {
        free(*sh);
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
        free(*sh);
        perror("No PATH found, don't delete the PATH env!");
        exit(EXIT_SUCCESS);
    }
}

// exits program if argc is not 1
void	argc_checker(int argc, t_sh_data **sh)
{
    if (argc != 1)
    {
        free(*sh);
        *sh = NULL;
        printf("Invalid argument count. Usage: ./minishell"); //to be replaced by fd_printf
        exit(EXIT_SUCCESS);
    }

}

int main(int argc, char **argv, char **envp)
{
    t_sh_data *sh;

    sh = (t_sh_data *)malloc(sizeof(t_sh_data));
    printf("argv[0] is: %s\n", argv[0]); //to be replaced by (void)argv
    argc_checker(argc, &sh);
    env_checker(envp, &sh);
    shell_init(&sh, envp);
    shell_loop(&sh);
    return 0;
}
