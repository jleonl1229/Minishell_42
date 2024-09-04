/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:40:10 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/04 19:43:50 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	using these functions to update the terminal inmediately and 
**	for not waiting until then next iteration of the loop
**	rl_on_new_line(); //prepares terminal for new input [UNPROTECTED]
**	rl_replace_line("", 0); //replaces current line with an empty string
**	rl_redisplay(); //refreshes the terminal display, showing the empty string{{{
** "If handle_sigint is called during get_input, it interrupts readline, 
**  and the loop resumes, causing get_input to be called again"
*/
void	handle_sigint(int sig)
{
	write(1, "\n", 1);
	if (sig != -7)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}


void	sig_blocking_handler(int sig)
{
	if (sig == SIGINT)
	{
		handle_sigint(-7);
		signal_received = 6;
	}
	else if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		signal_received = 7;
	}
}

/*
**	blocking command: halts execution of commands until condition is met.
**	examples:
**		1. cat (without arguments): waits for user input
**		2.	sleep: pauses execution for a specified amount of time
*/
void	blocking_cmd_sig(void)
{
	signal(SIGINT, sig_blocking_handler);
	signal(SIGQUIT, sig_blocking_handler);
}

void	heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = heredoc_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	signal_received = 1;
	write(1, "\n", 1);
}

void	e_pipe_sig_handler(int sig)
{
	write(1, "\n", 1);
	write(1, "$ ", 2);
	(void)sig;
	signal_received = 3;
}

/*
**	called at the beginning of shell_loop()
**	if signal_received == 0, no signal has been triggered before
**	if signal_received == 2, an ending pipe has been registered and custom
**	signals need to be applied	
*/
void	default_signals(void)
{
	if (signal_received == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (signal_received == 2)
	{
		signal_received = 0;
		signal(SIGINT, e_pipe_sig_handler);
	}
}
