extern int	status_code;

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	*out;
	t_big	big;

	big = struct_init(av, env); **TODO** //Parsing pour remplir la structure
	while(1)
	{
		**TODO**
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		free(str);
		if (!args_verif(out, &big))
			break;

	}
	exit(status_code);
}