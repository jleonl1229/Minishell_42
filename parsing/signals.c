/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleon-la <jleon-la@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:01:30 by jleon-la          #+#    #+#             */
/*   Updated: 2024/07/31 12:16:21 by jleon-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	handler_true(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return ;
}

static void	handler_false(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <dgomez-m@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:01:39 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/04/20 03:04:05 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initial idea for handling signals in minishell

static void	handler_true(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return ;
}

static void	handler_false(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	init_signals(bool *signal_cmd)
{
	if (*signal_cmd)
	{
		signal(SIGINT, &handler_true);
		signal(SIGQUIT, &handler_false);
	}
	else if (!*signal_cmd)
	{
		signal(SIGINT, &handler_false);
		signal(SIGQUIT, SIG_IGN);
		*signal_cmd = false;
	}
}
