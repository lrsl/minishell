/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:13:41 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/18 13:17:56 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)str;
	i = 0;
	while (i < n)
	{
		*ptr = (unsigned char)c;
		ptr++;
		i++;
	}
	return (str);
}

void	*ft_calloc(size_t nb, size_t size)
{
	char	*str;

	if (nb <= 0 || size <= 0)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(nb * size);
	if (!str)
		return (NULL);
	return (ft_memset(str, 0, nb * size));
}
