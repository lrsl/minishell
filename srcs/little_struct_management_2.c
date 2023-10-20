/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_struct_management_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:55:16 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 12:06:36 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	adapt_malloc(char const *s1)
{
	int	count;
	int	i;
	int	quote_double;
	int	quote_simple;

	i = 0;
	count = 0;
	quote_double = 0;
	quote_simple = 0;
	while (s1 && s1[i])
	{
		quote_simple = (quote_simple + (!quote_double && s1[i] == '\'')) % 2;
		quote_double = (quote_double + (!quote_simple && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !quote_simple) || (s1[i] == '\'' \
		&& !quote_double))
			count++;
		i++;
	}
	if (quote_simple || quote_double)
		return (-1);
	return (count);
}

char	*quote_trim(char const *s1, int quote_simple, int quote_double)
{
	int		count;
	int		i[2];
	char	*trimmed;

	i[1] = -1;
	i[0] = 0;
	count = adapt_malloc(s1);
	if (!s1 || count == -1)
		return (NULL);
	trimmed = malloc(sizeof(char) * (ft_strlen(s1) - count + 1));
	if (!trimmed)
		return (NULL);
	while (s1[i[0]])
	{
		quote_simple = (quote_simple + (!quote_double && s1[i[0]] == '\'')) % 2;
		quote_double = (quote_double + (!quote_simple && s1[i[0]] == '\"')) % 2;
		if ((s1[i[0]] != '\"' || quote_simple) && (s1[i[0]] != '\'' \
		|| quote_double) && ++i[1] >= 0)
			trimmed[i[1]] = s1[i[0]];
		i[0]++;
	}
	trimmed[++i[1]] = '\0';
	return (trimmed);
}
