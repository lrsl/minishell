/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:55:11 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 12:07:16 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status_code;

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	*displayed;
	t_big	big;

	big = struct_init(av, env);
	while (av && ac)
	{
		signal(SIGINT, signal_management);
		signal(SIGQUIT, SIG_IGN);
		str = custom_prompt(big);
		if (str)
			displayed = readline(str);
		else
			displayed = readline("guest@minishell $ ");
		free(str);
		if (!args_verif(displayed, &big))
			break ;
	}
	exit(g_status_code);
}
