/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triming_management_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:54:28 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 12:14:48 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_counting_words(char *s, char *target, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(target, s[i]))
		{
			while ((!ft_strchr(target, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_put_in_tab(char **tab, char *s, char *target, int i[3])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(target, s[i[0]]))
		{
			while ((!ft_strchr(target, s[i[0]]) || q[0] || q[1]) && s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		tab[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (tab);
}

char	**trim2(char const *s, char *target)
{
	char	**tab;
	int		nwords;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	nwords = ft_counting_words((char *)s, target, 0);
	if (nwords == -1)
		return (NULL);
	tab = malloc((nwords + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab = ft_put_in_tab(tab, (char *)s, target, i);
	tab[nwords] = NULL;
	return (tab);
}
