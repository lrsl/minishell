
int	recoded_builtin_cd(t_big *p)
{
	char	**str[2];
	char	*aux;

	status_code = 0;
	str[0] = ((t_little *)p->cmds->content)->command;
	aux = mini_getenv("HOME", p->env, 4);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_matrix(NULL, aux);
	free(aux);
	aux = getcwd(NULL, 0);
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	cd_error(str);
	if (!status_code)
		p->env = mini_setenv("OLDPWD", str[1][1], p->env, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	p->env = mini_setenv("PWD", str[1][2], p->env, 3);
	ft_free_matrix(&str[1]);
	return (status_code);
}

int	recoded_builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

int	recoded_builtin_echo(t_list *cmd)
{
	int		newline;
	int		i[2];
	char	**argv;
	t_little	*node;

	i[0] = 0;
	i[1] = 0;
	newline = 1;
	node = cmd->content;
	argv = node->command;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2) && \
			(ft_countchar(argv[i[0]], 'n') == \
			(int)(ft_strlen(argv[i[0]]) - 1)))
			newline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", newline) == 2);
}

int	recoded_builtin_export(t_big *big)
{
	int		ij[2];
	int		pos;
	char	**argv;

	argv = ((t_little *)big->cmds->content)->command;
	if (ft_matrixlen(argv) >= 2)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], big->env, ij);
			if (pos == 1)
			{
				free(big->env[ij[1]]);
				big->env[ij[1]] = ft_strdup(argv[ij[0]]);
			}
			else if (!pos)
				big->env = ft_extend_matrix(big->env, argv[ij[0]]);
			ij[0]++;
		}
	}
	return (0);
}

int	recoded_builtin_unset(t_big *big)
{
	char	**argv;
	char	*aux;
	int		ij[2];

	ij[0] = 0;
	argv = ((t_little *)big->cmds->content)->command;
	if (ft_matrixlen(argv) >= 2)
	{
		while (argv[++ij[0]])
		{
			if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] != '=')
			{
				aux = ft_strjoin(argv[ij[0]], "=");
				free(argv[ij[0]]);
				argv[ij[0]] = aux;
			}
			if (var_in_envp(argv[ij[0]], big->env, ij))
				ft_matrix_replace_in(&big->env, NULL, ij[1]);
		}
	}
	return (0);
}