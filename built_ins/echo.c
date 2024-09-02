#include "../minishell.h"

/*
**	had to do this executable with write() instead of printf() because for cases like
**	"echo -n "hello" >test" it would output to terminal instead of redirecting.
**	why? printf uses buffers (storing the output before sending it to fd) that send the output to
**	STDOUT when a buffer flush is triggered ('\n' for example), but when using the "-n" option 
**	it doesn't get triggered and the text isn't sent to the appropriate fd. With write() this doesn't 
**	happen because write() doesn't use buffers
*/

int mini_echo(t_sh_data *sh)
{
    char **cmd;
    int i;
    int newline;

    cmd = sh->parsed_header->cmd;
    i = 1;
    newline = 1;

    if (cmd[1] == NULL)  // "echo" only
    {
        ft_putendl_fd("", STDOUT_FILENO);
        return 0;
    }
    if (ft_strncmp(cmd[1], "-n", ft_strlen("-n")) == 0 
    && ft_strlen(cmd[1]) == ft_strlen("-n"))
    {
        newline = 0;
        i = 2;
    }
    while (cmd[i] != NULL)
    {
        write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
        if (cmd[i + 1] != NULL)
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if (newline)
        write(STDOUT_FILENO, "\n", 1);

    return 0;
}






















/*int mini_echo(t_sh_data *sh)
{
    char **cmd;
    int i;
	int newline;

    cmd = sh->parsed_header->cmd;
	i = 1;
	newline = 1;
    if (cmd[1] == NULL)  // "echo" only
    {
        printf("\n");
        return 0;
    }
    if (ft_strncmp(cmd[1], "-n", ft_strlen("-n")) == 0 
    && ft_strlen(cmd[1]) == ft_strlen("-n"))
    {
        newline = 0;
        i = 2;
    }
    while (cmd[i] != NULL)
    {
        printf("%s", cmd[i]);
        if (cmd[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
	else
        fflush(stdout);
    return 0;
}*/
