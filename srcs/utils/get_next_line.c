/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 11:04:35 by anmassy           #+#    #+#             */
/*   Updated: 2023/10/19 11:58:49 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	size_line(char *strings, int i)
// {
// 	if (!strings)
// 		return (-1);
// 	while (1)
// 	{
// 		if (strings[i] == '\n' || strings[i] == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// char	*get_next_line(int fd)
// {
// 	static char		*strings;
// 	char			*buffer;
// 	char			*line;
// 	int				ret;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buffer)
// 		return (NULL);
// 	ret = read(fd, buffer, BUFFER_SIZE);
// 	while (ret > 0)
// 	{
// 		buffer[ret] = '\0';
// 		strings = ft_strjoin(strings, buffer);
// 		if (ft_strchr(buffer, '\n'))
// 			break ;
// 		ret = read(fd, buffer, BUFFER_SIZE);
// 	}
// 	line = ft_substr(strings, 0, (size_line(strings, 0) + 1));
// 	ret = size_line(strings, 0) + 1;
// 	strings = ft_substr(strings, ret, (ft_strlen(strings) - ret));
// 	return (free(buffer), line);
// }

char *get_next_line(int fd)
{
    int i = 0;
    int rd = 0;
    char character;

    if (BUFFER_SIZE <= 0)
        return (NULL);
    char *buffer = malloc(100000); // check before the current BUFFER_SIZE and then malloc
    while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
    }
    buffer[i] = '\0';
    if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
        return (free(buffer), NULL);
    return (buffer);
}