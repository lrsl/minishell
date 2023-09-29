
char	**split_all(char **args, t_big *big)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (args && args[++i])
	{
		args[i] = expand_vars(args[i], -1, quotes, big);
		args[i] = expand_path(args[i], -1, quotes, \
			mini_getenv("HOME", big->env, 4));
		subsplit = ft_cmdsubsplit(args[i], "<|>");
		ft_matrix_replace_in(&args, subsplit, i);
		i += ft_matrixlen(subsplit) - 1;
		ft_free_matrix(&subsplit);
	}
	return (args);
}

void	*args_parsing(char **args, t_big *big)
{
	int	is_exit;
	int	i;

	is_exit = 0;
	big->commands = fill_nodes(split_all(args, big), -1);
	if (!big->commands)
		return (big);
	i = ft_lstsize(big->commands);
	status_code = builtin(big, big->commands, &is_exit, 0);
	while (i-- > 0)
		waitpid(-1, &status_code, 0);
	if (!is_exit && status_code == 13)
		status_code = 0;
	if (status_code > 255)
		status_code = status_code / 255;
	if (args && is_exit)
	{
		ft_lstclear(&big->commands, free_function);
		return (NULL);
	}
	return (big);
}

//debut du parsing
void	*args_verif(char *out, t_big *big)
{
	char	**tab;
	t_little	*node;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	tab = ft_cmdtrim(out, " "); //triming
	free(out);
	if (!tab)
		error_function(QUOTE, NULL, 1);
	if (!tab)
		return ("");
	big = args_parsing(tab, big);
	if (big && big->commands)
		node = big->commands->content;
	if (big && big->commands && node && node->command && ft_lstsize(big->commands) == 1)
		big->env = do_env("_", node->command[ft_tablen(node->command) - 1], big->env, 1);
	if (big && big->commands)
		ft_lstclear(&big->commands, free_function);
	return (big);
}
