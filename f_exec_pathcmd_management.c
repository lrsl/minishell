// Au debtu de l'exec, verifier les commandes, le path valide / le creer

static char	*verif_pathcommand(char **env_path, char *command, char *path)
{
	char	*temp;
	int		i;

	i = -1;
	path = NULL;
	while (env_path && env_path[++i])
	{
		free(path);
		temp = ft_strjoin(env_path[i], "/");
		if (!temp)
			return (NULL);
		path = ft_strjoin(temp, command);
		free(temp);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
	}
	if (!env_path || !env_path[i])
	{
		free(path);
		return (NULL);
	}
	return (path);
}

static DIR	*verif_cmd(t_big *struct, t_list *command, char ***s, char *path)
{
	t_little	*node;
	DIR		*dir;

	dir = NULL;
	node = command->content;
	if (node && node->command)
		dir = opendir(*node->command);
	if (node && node->command && ft_strchr(*node->command, '/') && !dir)
	{
		*s = ft_split(*node->command, '/');
		node->path = ft_strdup(*node->command);
		free(node->command[0]);
		node->command[0] = ft_strdup(s[0][ft_tablen(*s) - 1]);
	}
	else if (!verif_builtin(node) && node && node->command && !dir)
	{
		path = find_env("PATH", struct->env, 4); //function a faire avec Antoine
		*s = ft_split(path, ':');
		free(path);
		node->path = verif_pathcommand(*s, *node->command, node->path);
		if (!node->path || !node->command[0] || !node->command[0][0])
			error_function(NCMD, *node->command, 127);
	}
	return (dir);
}

void	access_command(t_big *struct, t_list *command, char **s, char *path)
{
	t_little	*node;
	DIR		*dir;

	node = command->content;
	dir = verif_cmd(struct, command, &s, path);
	if (!verif_builtin(node) && node && node->command && dir)
		error_function(IS_DIR, *node->command, 126);
	else if (!verif_builtin(node) && node && node->path && \
		access(node->path, F_OK) == -1)
		error_function(NDIR, node->path, 127);
	else if (!verif_builtin(node) && node && node->path && \
		access(node->path, X_OK) == -1)
		error_function(NPERM, node->path, 126);
	if (dir)
		closedir(dir);
	xxxx(&s); //function pour free s a coder pour dans le libft
}