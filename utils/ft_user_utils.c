
static void	new_out(char ***out, int fd)
{
	char	**tab;
	char	*tmp;
	char	*str;

	tab = NULL;
	str = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		tmp = ft_strtrim(str, "\n");
		free(str);
		tab = ft_biggertab(tab, tmp);
		free(tmp);
	}
	ft_tabfree(out);
	*out = tab;
}

void	get_user_util(char ***out, char *full, char *av, char **env)
{
	pid_t	pid;
	int		fd[2];
	char	**matrix;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		matrix = ft_split(av, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!access(full, F_OK))
			execve(full, matrix, env);
		exit (1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	new_out(out, fd[READ_END]);
	close(fd[READ_END]);
}
