// compte nombre de mots en fonction des espaces, en prenant en compte les quotes
static int	ft_wordcounting(const char *str, char *target, int count[2])
{
	int		quote[2];

	quote[0] = 0; //si on est dans une auote ou non ?
	quote[1] = 0; //quel type de quote ? ' ou "
	while (str[count[0]] != '\0')
	{
		if (!ft_strchr(target, str[count[0]]))
		{
			count[1]++;
			while ((!ft_strchr(target, str[count[0]]) || quote[0]) && str[count[0]] != '\0')
			{
				if (!quote[1] && (str[count[0]] == '\"' || str[count[0]] == '\''))
					quote[1] = str[count[0]];
				quote[0] = (quote[0] + (str[count[0]] == quote[1])) % 2;
				quote[1] *= quote[0] != 0;
				count[0]++;
			}
			if (quote[0])
				return (-1); //erreur si quote ouverte
		}
		else
			count[0]++;
	}
	return (count[1]);
}

// pour remplir le tableau avec les substr
static char	**put_in_tab(char **tab, char const *str, char *target, int i[3])
{
	int		len;
	int		quote[2];

	quote[0] = 0; // pour les single quotes
	quote[1] = 0; // pour les double quotes
	len = ft_strlen(str);
	while (str[i[0]])
	{
		while (ft_strchr(target, str[i[0]]) && str[i[0]] != '\0')
			i[0]++;
		i[1] = i[0]; // pour garder la trace de l'index de debut d'un mot / substring
		while ((!ft_strchr(target, str[i[0]]) || quote[0] || quote[1]) && str[i[0]])
		{
			quote[0] = (quote[0] + (!quote[1] && str[i[0]] == '\'')) % 2;
			quote[1] = (quote[1] + (!quote[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			tab[i[2]++] = "\0"; // si l'index > longueur de str, alors c'est la fin
		else
			tab[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (tab);
}

//premiere fonction de trim
//separe la string en fonction des espaces et des quotes
char	**trim1(char const *str, char *target)
{
	char	**tab;
	int		word_counter;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!str)
		return (NULL);
	word_counter = ft_wordcounting(str, target, counts);
	if (word_counter == -1)
		return (NULL);
	tab = malloc((word_counter + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = put_in_tab(tab, str, target, i);
	tab[word_counter] = NULL;
	return (tab);
}

