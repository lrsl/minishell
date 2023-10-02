
// on reinitialise chaque node avant de le remplir
static t_little	*prepare_little(void)
{
	t_little	*little;

	little = malloc(sizeof(t_little));
	if (!little)
		return (NULL);
	little->command = NULL;
	little->path = NULL;
	little->infile = STDIN_FILENO;
	little->outfile = STDOUT_FILENO;
	return (little);
}

// va remplir les params de little selon les types des arguments
static t_little	*adapt_to_param_type(t_little *node, char **a[2], int *i)
{
	if (a[0][*i])
	{
		if (a[0][*i][0] == '>' && a[0][*i + 1] && a[0][*i + 1][0] == '>')
			node = manage_outfile_2(node, a[1], i);
		else if (a[0][*i][0] == '>')
			node = manage_outfile_1(node, a[1], i);
		else if (a[0][*i][0] == '<' && a[0][*i + 1] && a[0][*i + 1][0] == '<')
			node = manage_infile_2(node, a[1], i);
		else if (a[0][*i][0] == '<')
			node = manage_infile_1(node, a[1], i);
		else if (a[0][*i][0] != '|')
			node->command = ft_biggertab(node->command, a[1][*i]);
		else
		{
			error_function(PIPENDERR, NULL, 2);
			*i = -2;
		}
		return (node);
	}
	error_function(PIPENDERR, NULL, 2);
	*i = -2;
	return (node);
}

//classic trim ou on dupliaue puis on retire les whitespaces
static char	**dup_trim(char **tab_of_args)
{
	char	**tmp_tab;
	char	*tmp_str;
	int		i;

	i = -1;
	tmp_tab = ft_duptab(tab_of_args); // on dup
	while (tmp_tab && tmp_tab[++i])
	{
		tmp_str = quote_trim(tmp_tab[i], 0, 0); //on trim
		free(tmp_tab[i]);
		tmp_tab[i] = tmp_str;
	}
	return (tmp_tab);
}

// mettre fin a la liste chainée
static t_list	*filling_finished(t_list *cmds, char **args, char **temp)
{
	ft_lstclear(&cmds, free_content);
	ft_tabfree(&temp);
	ft_tabfree(&args);
	return (NULL);
}

// prend un tabvleau d'arguments, le trim, puis cree une liste chainee de little, remplie des arguments selon leur type
t_list	*put_in_nodes(char **tab_of_args, int i)
{
	t_list	*cmds[2];
	char	**temp[2];

	cmds[0] = NULL;
	temp[1] = dup_trim(tab_of_args);
	while (tab_of_args[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]); // on crée la liste chainée de 'little'
		if (i == 0 || (tab_of_args[i][0] == '|' && tab_of_args[i + 1] && tab_of_args[i + 1][0]))
		{
			i += tab_of_args[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(prepare_little()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		temp[0] = tab_of_args;
		cmds[1]->content = adapt_to_param_type(cmds[1]->content, temp, &i); //on va remplir en fonction du type de param
		if (i < 0)
			return (filling_finished(cmds[0], tab_of_args, temp[1]));
		if (!tab_of_args[i])
			break ;
	}
	ft_tabfree(&temp[1]);
	ft_tabfree(&tab_of_args);
	return (cmds[0]);
}

