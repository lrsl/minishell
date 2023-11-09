/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:55:11 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/09 11:42:00 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status_code;

void	ft_save_pwd_value(t_big *big)
{
	char	*buf_pwd;

	buf_pwd = getcwd(NULL, 0);
	if (buf_pwd)
	{
		if (big->pwd_save)
			free(big->pwd_save);
		big->pwd_save = getcwd(NULL, 0);
	}
	free(buf_pwd);
}

void	*main_exec(t_big *bigstruct, t_list *command)
{
	int		fd[2];

	access_command(bigstruct, command, NULL, NULL);
	if (pipe(fd) == -1)
		return (error_function(PIPERR, NULL, 1));
	if (!forking_verif(bigstruct, command, fd))
		return (NULL);
	close(fd[WRITE_END]);
	if (command->next && !((t_little *)command->next->content)->infile)
		((t_little *)command->next->content)->infile = fd[READ_END];
	else
		close(fd[READ_END]);
	if (((t_little *)command->content)->infile > 2)
		close(((t_little *)command->content)->infile);
	if (((t_little *)command->content)->outfile > 2)
		close(((t_little *)command->content)->outfile);
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	*displayed;
	t_big	big;

	if (!isatty(0))
		exit (1);
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
		{
			free(big.pwd_save);
			break ;
		}
	}
	ft_tabfree(&big.env);
	exit(g_status_code);
}
