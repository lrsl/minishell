/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:04:35 by anmassy           #+#    #+#             */
/*   Updated: 2023/10/19 11:20:28 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	size_line(char *strings, int i)
{
	if (!strings)
		return (-1);
	while (1)
	{
		if (strings[i] == '\n' || strings[i] == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char		*strings;
	char			*buffer;
	char			*line;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		strings = ft_strjoin(strings, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	line = ft_substr(strings, 0, (size_line(strings, 0) + 1));
	ret = size_line(strings, 0) + 1;
	strings = ft_substr(strings, ret, (ft_strlen(strings) - ret));
	return (free(buffer), line);
}
