// execution de minishell


void	child_process_builtin(t_big *struct, t_little *node, int len, t_list *command)
{
	signal(); //finir de voir ensemble si ok ? necessaire ?
	if (!verif_builtin(node) && node->full_cmd)
		execve(node->full_path, node->full_cmd, struct->envp);
	else if (node->full_cmd && !ft_strncmp(*node->full_cmd, "pwd", len) \
		&& len == 3)
		g_status = // function oour choper le status exit code
	else if (verif_builtin(node) && node->full_cmd && \
		!ft_strncmp(*node->full_cmd, "echo", len) && len == 4)
		g_status = // builtin echo a faire
	else if (verif_builtin(node) && node->full_cmd && \
		!ft_strncmp(*node->full_cmd, "env", len) && len == 3)
	{
		xxxx(struct->envp, 1, 1); //function pour le fd du tab, voir notes dans obsidian
		g_status = 0;
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
	if (node->full_cmd)
		len = ft_strlen(*node->full_cmd);
	child_process_next(command, fd);
	close(fd[READ_END]);
	child_process_builtin(struct, node, len, command);
	ft_lstclear(&struct->commands, free_content);
	exit(g_status);
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
	if (node->full_cmd)
		dir = opendir(*node->full_cmd);
	if (node->infile == -1 || node->outfile == -1)
		return (NULL);
	if ((node->full_path && access(node->full_path, X_OK) == 0) || verif_builtin(node))
		forking_exec(struct, command, fd);
	else if (!verif_builtin(node) && ((node->full_path && \
		!access(node->full_path, F_OK)) || dir))
		g_status = 126;
	else if (!verif_builtin(node) && node->full_cmd)
		g_status = 127;
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

