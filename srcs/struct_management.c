/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:54:39 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/18 12:04:16 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	status_code;

/* Rempli la structure */
t_big	fill_struct(t_big struct, char *str, char **av)
{
	//remplir struct
	char	*nb;
	str = getcwd(NULL, 0); //on chope le cwd
	struct.env = do_env("PWD", str, struct.env, 3); //trouver le bon pwd
	free(str);
	str = find_env("SHLVL", struct.env, 5) //recup SHLVL
	if (!str || ft_atoi(str) <= 0)
		nb = ft_strdup("1");
	else
		nb = ft_itoa(ft_atoi(str) + 1);
	free(str);
	struct.env = do_env("SHLVL", nb, struct.env, 5); //recuperer le niveau de shell
	str = find_env("PATH", struct.env, 4);
	if (!str)
		struct.env = do_env("PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", struct.env, 4);
	free(str);
	str = find_env("_", struct.env, 1);
	if (!str)
		struct.env = do_env("_", av[0], struct.env, 1);
	free(str);
	return (struct);
}

// on chope le pid
void	ft_getpid(t_big *struct)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		error_function(FORKERR, NULL, 1);
		ft_tabfree(&struct->env);
		exit(1);
	}
	if (!pid)
	{
		ft_tabfree(&struct->env);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	struct->pid = pid - 1;
}

// utile : https://riptutorial.com/bash/topic/4797/internal-variables

/* Met la structure a zero */
t_big	struct_init(char **av, char **env)
{
	t_big	struct;
	char	*str;

	str = NULL;
	struct.commands = NULL;
	struct.env = ft_duptab(env); //copie de env
	status_code = 0;
	ft_getpid(&struct);
	struct = fill_struct(struct, str, av); //remplir la structure avec les vraies valeurs
	return (struct);
}