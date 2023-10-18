/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exec_mainpart.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:55:48 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/18 12:03:14 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	status_code;

// execution de minishell


void	child_process_builtin(t_big *struct, t_little *node, int len, t_list *command)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!verif_builtin(node) && node->command)
		execve(node->path, node->command, struct->env);
	else if (node->command && !ft_strncmp(*node->command, "pwd", len) \
		&& len == 3)
		status_code =  recoded_builtin_pwd();// function oour choper le status exit code et le pwd
	else if (verif_builtin(node) && node->command && \
		!ft_strncmp(*node->command, "echo", len) && len == 4)
		status_code = recoded_builtin_echo(cmd);// builtin echo a faire
	else if (verif_builtin(node) && node->command && \
		!ft_strncmp(*node->command, "env", len) && len == 3)
	{
		ft_puttab_fd(struct->env, 1, 1);
		status_code = 0;
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

void	*child_process(t_big *struct, t_list *command, int fd[2])
{
	t_little	*node;
	int		len;

	node = command->content;
	len = 0;
	if (node->command)
		len = ft_strlen(*node->command);
	child_process_next(command, fd);
	close(fd[READ_END]);
	child_process_builtin(struct, node, len, command);
	ft_lstclear(&struct->commands, free_content);
	exit(status_code);
}

void	forking_exec(t_big *struct, t_list *command, int fd[2])
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
		child_process(struct, command, fd);
}


void	*forking_verif(t_big *struct, t_list *command, int fd[2])
{
	t_little	*node;
	DIR		*dir;

	node = command->content;
	dir = NULL;
	if (node->command)
		dir = opendir(*node->command);
	if (node->infile == -1 || node->outfile == -1)
		return (NULL);
	if ((node->path && access(node->path, X_OK) == 0) || verif_builtin(node))
		forking_exec(struct, command, fd);
	else if (!verif_builtin(node) && ((node->path && \
		!access(node->path, F_OK)) || dir))
		status_code = 126;
	else if (!verif_builtin(node) && node->command)
		status_code = 127;
	if (dir)
		closedir(dir);
	return ("");
}


//debut de la partie exec
void	*main_exec(t_big *struct, t_list *command)
{
	int		fd[2];

	access_command(struct, command, NULL, NULL);
	if (pipe(fd) == -1)
		return (error_function(PIPERR, NULL, 1)); //erreur de pipe donc function error qui correspond
	if (!forking_verif(struct, command, fd))
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

