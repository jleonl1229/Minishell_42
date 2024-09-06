/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:45:40 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 17:55:57 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if every env_var or PATH have been deleted
int	env_checker(char **envp, t_sh_data **sh)
{
	int	path_found;

	(void)sh;
	path_found = 0;
	if (envp == NULL || *envp == NULL)
	{
		printf("No ENV found, don't delete ENVs!");
		return 1;
	}
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", ft_strlen("PATH=")) == 0)
		{
			path_found = 1;
			break ;
		}
		envp++;
	}
	if (path_found == 0)
	{
		//printf("bash: %s: No such file or directory\n", (*sh)->prev_line);
		return 2;
	}
	return 0;
}

// exits program if argc is not 1
void	argc_checker(int argc, t_sh_data **sh)
{
	if (argc != 1)
	{
		free(*sh);
		*sh = NULL;
		printf("Invalid argument count. Usage: ./minishell\n");
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_sh_data	*sh;

	(void)argv;
	sh = (t_sh_data *)malloc(sizeof(t_sh_data));
	if (sh == NULL)
	{
		printf("malloc failure in main\n");
		exit(1);
	}
	argc_checker(argc, &sh);
	if (env_checker(envp, &sh) == 1)
	{
		free(sh);
		exit(1);
	}
	shell_init(&sh, envp);
	shell_loop(&sh, -1, 0);
	return (0);
}
