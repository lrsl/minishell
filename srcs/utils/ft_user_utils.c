/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_user_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:51:10 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/18 11:52:53 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_out(char ***out, int fd)
{
	char	**tab;
	char	*tmp;
	char	*str;

	tab = NULL;
	str = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		tmp = ft_strtrim(str, "\n");
		free(str);
		tab = ft_biggertab(tab, tmp);
		free(tmp);
	}
	ft_tabfree(out);
	*out = tab;
}

void	get_user_util(char ***out, char *full, char *av, char **env)
{
	pid_t	pid;
	int		fd[2];
	char	**tab;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		tab = ft_split(av, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (!access(full, F_OK))
			execve(full, tab, env);
		exit (1);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	new_out(out, fd[READ_END]);
	close(fd[READ_END]);
}
