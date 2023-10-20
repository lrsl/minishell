/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:53:28 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 11:56:13 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	uns_c;

	uns_c = (unsigned char)c;
	if (uns_c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (*str != '\0')
	{
		if (*str == uns_c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

int	ft_strchr_n(const char *str, int c)
{
	unsigned char	uns_c;
	int				i;

	i = 0;
	if (!str)
		return (-1);
	uns_c = (unsigned char)c;
	while (str[i] != '\0')
	{
		if (str[i] == uns_c)
			return (i);
		i++;
	}
	if (uns_c == '\0')
		return (i);
	return (-1);
}

int	ft_strchr_str(const char *str, char *str2)
{
	int				i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (ft_strchr(str2, str[i]))
			return (i);
		i++;
	}
	return (-1);
}
