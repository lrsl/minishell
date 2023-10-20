/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:56:10 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 12:13:32 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// gestion de l'env

int	var_env(char *av, char **env, int tab[2])
{
	int	position;

	tab[1] = 0;
	position = ft_strchr_n(av, '=');
	if (position == -1)
		return (-1);
	while (env[tab[1]])
	{
		if (!ft_strncmp(env[tab[1]], av, position + 1))
			return (1);
		tab[1]++;
	}
	return (0);
}

char	*find_env(char *var, char **env, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && env && env[i])
	{
		n2 = n;
		if (n2 < ft_strchr_n(env[i], '='))
			n2 = ft_strchr_n(env[i], '=');
		if (!ft_strncmp(env[i], var, n2))
			return (ft_substr(env[i], n2 + 1, ft_strlen(env[i])));
		i++;
	}
	return (NULL);
}

char	**do_env(char *str, char *value, char **env, int n)
{
	int		i[2];
	char	*tab[2];

	if (n < 0)
		n = ft_strlen(str);
	i[0] = -1;
	tab[0] = ft_strjoin(str, "=");
	tab[1] = ft_strjoin(tab[0], value); //on cree donc PWD=*data du getcwd*
	free(tab[0]);
	while (!ft_strchr(str, '=') && env && env[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_n(env[i[0]], '='))
			i[1] = ft_strchr_n(env[i[0]], '=');
		if (!ft_strncmp(env[i[0]], str, i[1]))
		{
			tab[0] = env[i[0]];
			env[i[0]] = tab[1];
			free(tab[0]);
			return (env);
		}
	}
	env = ft_biggertab(env, tab[1]);
	free(tab[1]);
	return (env);
}
