/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:56:33 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 14:19:02 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status_code;

int	builtin(t_big *big, t_list *cmd, int *is_exit, int n)
{
	char	**a;

	while (cmd)
	{
		a = ((t_little *)cmd->content)->command;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_status_code = recoded_builtin_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_status_code = recoded_builtin_cd(big);
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			g_status_code = recoded_builtin_export(big);
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
			g_status_code = recoded_builtin_unset(big);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			main_exec(big, cmd);
		}
		cmd = cmd->next;
	}
	return (g_status_code);
}

int	verif_builtin(t_little *node)
{
	int		l;

	if (!node->command)
		return (0);
	if ((node->command && ft_strchr(*node->command, '/')) \
		|| (node->path && ft_strchr(node->path, '/')))
		return (0);
	l = ft_strlen(*node->command);
	if (!ft_strncmp(*node->command, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->command, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->command, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*node->command, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*node->command, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*node->command, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*node->command, "exit", l) && l == 4)
		return (1);
	return (0);
}
