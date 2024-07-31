/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:55:38 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 11:56:14 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Dejo este ejemplo por aqi para mirarmelo

bool	check_if_exist(t_shell *env, char *name, char *value)
{
	t_my_env	*tmp;

	tmp = env->env_list;
	while (tmp)
	{
		if (check_names(tmp->name, name))
		{
			free(tmp->value);
			tmp->value = value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	equal_handler(t_shell *shell, char *name, char *value)
{
	if (check_if_exist(shell, name, value))
		return (free(name));
	add_env(&shell->env_list, ft_envnew(name, value, shell->env_list));
	if (shell->env_sys_end->next)
		sort_env(shell->env_sys_end->next);
}

void	realloc_env(t_shell *shell, char **newvar, bool *error_handler)
{
	int		i;
	char	*split[2];
	bool	local_error;

	local_error = false;
	i = 0;
	while (newvar[++i])
	{
		local_error = false;
		handle_split_env(&split[0], &split[1], newvar[i]);
		handle_errors_export(split[0], &local_error);
		if (local_error)
		{
			*error_handler = true;
			free(split[0]);
			free(split[1]);
			continue ;
		}
		equal_handler(shell, split[0], split[1]);
	}
}

int	export(t_shell *shell, char **cmd)
{
	bool	error_handler;

	error_handler = false;
	if (!cmd[1])
	{
		print_env(shell->env_list);
		return (0);
	}
	realloc_env(shell, cmd, &error_handler);
	get_things(shell, true);
	return ((int)error_handler);
}