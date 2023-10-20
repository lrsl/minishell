/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:54:39 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 14:20:25 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status_code;

t_big	fill_struct(t_big bigstruct, char *str, char **av)
{
	char	*nb;

	str = getcwd(NULL, 0);
	bigstruct.env = do_env("PWD", str, bigstruct.env, 3);
	free(str);
	str = find_env("SHLVL", bigstruct.env, 5);
	if (!str || ft_atoi(str) <= 0)
		nb = ft_strdup("1");
	else
		nb = ft_itoa(ft_atoi(str) + 1);
	free(str);
	bigstruct.env = do_env("SHLVL", nb, bigstruct.env, 5);
	str = find_env("PATH", bigstruct.env, 4);
	if (!str)
		bigstruct.env = do_env("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", bigstruct.env, 4);
	free(str);
	str = find_env("_", bigstruct.env, 1);
	if (!str)
		bigstruct.env = do_env("_", av[0], bigstruct.env, 1);
	free(str);
	return (bigstruct);
}

void	ft_getpid(t_big *bigstruct)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		error_function(FORKERR, NULL, 1);
		ft_tabfree(&bigstruct->env);
		exit(1);
	}
	if (!pid)
	{
		ft_tabfree(&bigstruct->env);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	bigstruct->pid = pid - 1;
}

t_big	struct_init(char **av, char **env)
{
	t_big	bigstruct;
	char	*str;

	str = NULL;
	bigstruct.commands = NULL;
	bigstruct.env = ft_duptab(env);
	g_status_code = 0;
	ft_getpid(&bigstruct);
	bigstruct = fill_struct(bigstruct, str, av);
	return (bigstruct);
}
