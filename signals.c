/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizem <mizem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:37:25 by abdennac          #+#    #+#             */
/*   Updated: 2024/10/21 23:41:39 by mizem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	// rl_replace_line("", 0); // Clear current input line
	rl_on_new_line();		// Move cursor to new prompt
	rl_redisplay();			// Redisplay prompt
}

void handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}