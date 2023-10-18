/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:53:49 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/18 13:17:51 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strlen_static(const char *s)
{
	int	count;

	count = 0;
	if (!s)
		return (count);
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

int	ft_putchar_fd(char c, int fd)
{
	return ((int)write(fd, &c, 1));
}

int	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen_static(s)));
	return (0);
}

int	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
		return ((int)ft_strlen_static(s) + 1);
	}
	return (0);
}

int	ft_puttab_fd(char **tab, int nl, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (tab && tab[i])
	{
		if (nl)
			count += ft_putendl_fd(tab[i], fd);
		else
			count += ft_putstr_fd(tab[i], fd);
		i++;
	}
	return (count);
}

