/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:55:34 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/18 12:39:44 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	status_code;

//gestion du heredoc (reprendre celui de pipex)

char	*ft_here_doc_str(char *str[2], size_t len, char *limit, char *trigger)
{
	char	*temp;

	while (status_code != 130 && (!str[0] || ft_strncmp(str[0], limit, len) || ft_strlen(limit) != len))
	{
		temp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(temp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", trigger, limit);
			break ;
		}
		temp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(temp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	ft_here_doc(char *str[2], char *aux[2])
{
	int		fd[2];

	status_code = 0;
	if (pipe(fd) == -1)
	{
		error_function(PIPERR, NULL, 1);
		return (-1);
	}
	str[1] = ft_here_doc_str(str, 0, aux[0], aux[1]);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (status_code == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
