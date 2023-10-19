/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsl <rsl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:54:46 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/19 22:42:55 by rsl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	status_code;

//gestion des signal
void	signal_management(int signal)
{
	if (signal == SIGINT)
	{
		status_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}


// void rl_replace_line (const char *text, int clear_undo) ---> CF SUBJECT
// Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

// int rl_on_new_line () ---> CF SUBJECT
// Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
