// Au debtu de l'exec, verifier les commandes, le path valide / le creer

static char	*verif_pathcommand(char **env_path, char *command, char *full_path)
{
	char	*temp;
	int		i;

	i = -1;
	full_path = NULL;
	while (env_path && env_path[++i])
	{
		free(full_path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static DIR	*verif_cmd(t_big *struct, t_list *command, char ***s, char *path)
{
	t_little	*node;
	DIR		*dir;

	dir = NULL;
	node = command->content;
	if (node && node->full_cmd)
		dir = opendir(*node->full_cmd);
	if (node && node->full_cmd && ft_strchr(*node->full_cmd, '/') && !dir)
	{
		*s = ft_split(*node->full_cmd, '/');
		node->full_path = ft_strdup(*node->full_cmd);
		free(node->full_cmd[0]);
		node->full_cmd[0] = ft_strdup(s[0][ft_tablen(*s) - 1]);
	}
	else if (!verif_builtin(node) && node && node->full_cmd && !dir)
	{
		path = mini_getenv("PATH", struct->envp, 4); //function a faire avec Antoine
		*s = ft_split(path, ':');
		free(path);
		node->full_path = verif_pathcommand(*s, *node->full_cmd, node->full_path);
		if (!node->full_path || !node->full_cmd[0] || !node->full_cmd[0][0])
			error_function(NCMD, *node->full_cmd, 127);
	}
	return (dir);
}

void	access_command(t_big *struct, t_list *command, char **s, char *path)
{
	t_little	*node;
	DIR		*dir;

	node = command->content;
	dir = verif_cmd(struct, command, &s, path);
	if (!verif_builtin(node) && node && node->full_cmd && dir)
		error_function(IS_DIR, *node->full_cmd, 126);
	else if (!verif_builtin(node) && node && node->full_path && \
		access(node->full_path, F_OK) == -1)
		error_function(NDIR, node->full_path, 127);
	else if (!verif_builtin(node) && node && node->full_path && \
		access(node->full_path, X_OK) == -1)
		error_function(NPERM, node->full_path, 126);
	if (dir)
		closedir(dir);
	xxxx(&s); //function pour free s a coder pour dans le libft
}