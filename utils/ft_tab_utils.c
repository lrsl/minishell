
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}


char	**ft_duptab(char **tab)
{
	char	**out;
	int		n_rows;
	int		i;

	i = 0;
	n_rows = ft_tablen(tab);
	out = malloc(sizeof(char *) * (n_rows + 1));
	if (!out)
		return (NULL);
	while (tab[i])
	{
		out[i] = ft_strdup(tab[i]);
		if (!out[i])
		{
			ft_free_matrix(&out);
			return (NULL);
		}
		i++;
	}
	out[i] = NULL;
	return (out);
}


//to add to libft, to free a nxn tab

void	ft_tabfree(char ***tab)
{
	int	i;

	i = 0;
	while (tab && tab[0] && tab[0][i])
	{
		free(tab[0][i]);
		i++;
	}
	if (tab)
	{
		free(tab[0]);
		*tab = NULL;
	}
}

char	**ft_biggertab(char **in, char *newstr)
{
	char	**out;
	int		len;
	int		i;

	i = -1;
	out = NULL;
	if (!newstr)
		return (in);
	len = ft_tablen(in);
	out = malloc(sizeof(char *) * (len + 2));
	out[len + 1] = NULL;
	if (!out)
		return (in);
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
		{
			ft_tabfree(&in);
			ft_tabfree(&out);
		}
	}
	out[i] = ft_strdup(newstr);
	ft_tabfree(&in);
	return (out);
}
