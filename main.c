extern int	status_code;

int	main(int ac, char **av, char **env)
{
	char	*str;
	char	*displayed;
	t_big	big;

	big = struct_init(av, env); //Parsing pour remplir la structure
	while(av && ac)
	{
		signal(SIGINT, signal_management);
		signal(SIGQUIT, SIG_IGN);
		str = custom_prompt(big); //gerer le prompt
		if (str)
			displayed = readline(str);
		else
			displayed = readline("guest@minishell $ ");
		free(str);
		if (!args_verif(displayed, &big))
			break ;
	}
	exit(status_code);
}
