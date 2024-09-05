/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:42:39 by mzuloaga          #+#    #+#             */
/*   Updated: 2024/09/05 16:04:19 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	e_pipe_sig_handler(int sig)
{
	write(1, "\n", 1);
	write(1, "$ ", 2);
	(void)sig;
	g_signal = 3;
}

/*
**	called at the beginning of shell_loop()
**	if g_signal == 0, no signal has been triggered before
**	if g_signal == 2, an ending pipe has been registered and custom
**	signals need to be applied	
*/
void	default_signals(void)
{
	if (g_signal == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (g_signal == 2)
	{
		g_signal = 0;
		signal(SIGINT, e_pipe_sig_handler);
	}
}

/*
**  updates last_exit_status to 130 or 131 if a signal has been used
**  with a blocking cmd
*/
void	status130_131(t_sh_data *sh)
{
	if (g_signal == 1 || g_signal == 6 || g_signal == 3)
	{
		free(sh->last_exit_status);
		sh->last_exit_status = ft_strdup("130");
		g_signal = 0;
	}
	else if (g_signal == 7)
	{
		free(sh->last_exit_status);
		sh->last_exit_status = ft_strdup("131");
		g_signal = 0;
	}
}
