/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:19:37 by jleon-la          #+#    #+#             */
/*   Updated: 2024/09/04 19:19:47 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
