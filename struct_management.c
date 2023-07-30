/* Rempli la structure */
t_big	fill_struct(t_big struct, char *str, char **av)
{
	//remplir struct
	str = getcwd(NULL, 0);
	struct.env = do_env("PWD", str, struct.env, 3) //trouver le bon pwd
	free(str);
	str = find_env("SHLVL", struct.env, 5) //recup SHLVL
	if !str ou atoi(str0=) <= 0
		num = 1;
	else num = atoi(str) + 1
	free(str);
	struct.env = do_env("SHLVL", num, struct.env, 5); //recuperer le niveau de shell
	str = find_env("PATH", struct.env, 4);
	if (!str)
		str = find_env(" FULL PATH XXXXX" ... ...)
	free(str);
	return (struct);
}

// utile : https://riptutorial.com/bash/topic/4797/internal-variables

/* Met la structure a zero */
t_big	struct_init(char **av, char **env)
{
	t_big	struct;
	char	*str;

	str = NULL;
	struct.commands = NULL;
	struct.env = **TODO** //copie de env
	status_code = 0;
	pid = **TODO** //fork et recuperer le pid
	struct = fill_struct(struct, str, av); //remplir la structure avec les vraies valeurs
	return (struct);
}