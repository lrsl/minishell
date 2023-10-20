/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:56:18 by anmassy           #+#    #+#             */
/*   Updated: 2023/10/20 11:57:19 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	ft_strlen_nbr(long nb)
{
	size_t	len;

	len = 1;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*string;

	nb = n;
	len = ft_strlen_nbr(nb);
	string = (char *)malloc((len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	string[len--] = '\0';
	if (nb == 0)
		string[0] = '0';
	if (nb < 0)
	{
		string[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		string[len] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	return (string);
}
