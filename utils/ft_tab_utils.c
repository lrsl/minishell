
int	ft_tablen(char **m)
{
	int	i;

	i = 0;
	while (m && m[i])
		i++;
	return (i);
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