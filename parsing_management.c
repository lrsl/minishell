
// on expand les variables, on resplit et on remet tout dans tab
char	**final_split(char **tab, t_big *big)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (tab && tab[++i])
	{
		tab[i] = var_expanding(tab[i], -1, quotes, big); //expand les var $
		tab[i] = path_expanding(tab[i], -1, quotes,	find_env("HOME", big->env, 4));
		subsplit = trim2(tab[i], "<|>"); //on split encore avec <, > et |
		ft_tab_row_n_replace(&tab, subsplit, i); //on actualise dans tab
		i += ft_tablen(subsplit) - 1;
		ft_tabfree(&subsplit);
	}
	return (tab);
}

void	*args_parsing(char **tab, t_big *big)
{
	int	trigger;
	int	i;

	trigger = 0;
	big->commands = put_in_nodes(final_split(tab, big), -1); //final_split : on resplit. put_in_nodes : on met les morceaux dans les structures s_little
	if (!big->commands) //si erreur on garde big unchanged
		return (big);
	i = ft_lstsize(big->commands); //on calcule la taille de la liste créée
	status_code = builtin(big, big->commands, &trigger, 0); //on appelle les builtins
	while (i-- > 0) //tant que la liste chainée existe
		waitpid(-1, &status_code, 0); //on attend le child process
	if (!trigger && status_code == 13)
		status_code = 0;
	if (status_code > 255)
		status_code = status_code / 255;
	if (tab && trigger)
	{
		ft_lstclear(&big->commands, free_function);
		return (NULL);
	}
	return (big);
}

//debut du parsing
void	*args_verif(char *out, t_big *big)
{
	char		**tab;
	t_little	*node;

	if (!out)
	{
		printf("exit\n");
		return (NULL); //donne lieu au break dans le main
	}
	if (out[0] != '\0')
		add_history(out); //sinon on ajoute a l'history
	tab = trim1(out, " "); //first triming avec les spaces et les quotes
	free(out);
	if (!tab)
		error_function(QUOTE, NULL, 1);
	if (!tab)
		return ("");
	big = args_parsing(tab, big); //gros du parsing
	if (big && big->commands)
		node = big->commands->content;
	if (big && big->commands && node && node->command && ft_lstsize(big->commands) == 1)
		big->env = do_env("_", node->command[ft_tablen(node->command) - 1], big->env, 1);
	if (big && big->commands)
		ft_lstclear(&big->commands, free_function);
	return (big);
}
