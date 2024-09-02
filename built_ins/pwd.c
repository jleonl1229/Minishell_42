#include "../minishell.h"

int	mini_pwd(void)
{
	char	pwd[MAX_PATH];

	if (getcwd(pwd, MAX_PATH) == NULL)
	{
		perror("pwd");
		return 1;
	}
	printf("%s\n", pwd);
	return (0);
}
