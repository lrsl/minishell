/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exec_mainpart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:55:48 by rroussel          #+#    #+#             */
/*   Updated: 2023/11/06 10:18:59 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status_code;

void	child_process_builtin(t_big *bigstruct, t_little *node, int len, \
	t_list *cmd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!verif_builtin(node) && node->command)
		execve(node->path, node->command, bigstruct->env);
	else if (node->command && !ft_strncmp(*node->command, "pwd", len) \
		&& len == 3)
		g_status_code = recoded_builtin_pwd();
	else if (verif_builtin(node) && node->command && \
		!ft_strncmp(*node->command, "echo", len) && len == 4)
		g_status_code = recoded_builtin_echo(cmd);
	else if (verif_builtin(node) && node->command && \
		!ft_strncmp(*node->command, "env", len) && len == 3)
	{
		ft_puttab_fd(bigstruct->env, 1, 1);
		g_status_code = 0;
	}
}

static void	*child_process_next(t_list *command, int fd[2])
{
	t_little	*node;

	node = command->content;
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			return (error_function(DUPERR, NULL, 1));
		close(node->infile);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			return (error_function(DUPERR, NULL, 1));
		close(node->outfile);
	}
	else if (command->next && dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		return (error_function(DUPERR, NULL, 1));
	close(fd[WRITE_END]);
	return ("");
}

void	*child_process(t_big *bigstruct, t_list *command, int fd[2])
{
	t_little	*node;
	int			len;

	node = command->content;
	len = 0;
	if (node->command)
		len = ft_strlen(*node->command);
	child_process_next(command, fd);
	close(fd[READ_END]);
	child_process_builtin(bigstruct, node, len, command);
	ft_tabfree(&bigstruct->env); //ici
	ft_lstclear(&bigstruct->commands, free_function);
	exit(g_status_code);
}

void	forking_exec(t_big *bigstruct, t_list *command, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		error_function(FORKERR, NULL, 1);
	}
	else if (!pid)
		child_process(bigstruct, command, fd);
}

void	*forking_verif(t_big *bigstruct, t_list *command, int fd[2])
{
	t_little	*node;
	DIR			*dir;

	node = command->content;
	dir = NULL;
	if (node->command)
		dir = opendir(*node->command);
	if (node->infile == -1 || node->outfile == -1)
		return (NULL);
	if ((node->path && access(node->path, X_OK) == 0) || verif_builtin(node))
		forking_exec(bigstruct, command, fd);
	else if (!verif_builtin(node) && ((node->path && \
		!access(node->path, F_OK)) || dir))
		g_status_code = 126;
	else if (!verif_builtin(node) && node->command)
		g_status_code = 127;
	if (dir)
		closedir(dir);
	return ("");
}
