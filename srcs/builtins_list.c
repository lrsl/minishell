/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:54:22 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/18 12:01:54 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	status_code;

int	recoded_builtin_cd(t_big *big)
{
	char	**str[2];
	char	*aux;

	status_code = 0;
	str[0] = ((t_little *)big->commands->content)->command;
	aux = find_env("HOME", big->env, 4);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_biggertab(NULL, aux);
	free(aux);
	aux = getcwd(NULL, 0);
	str[1] = ft_biggertab(str[1], aux);
	free(aux);
	cd_error(str);
	if (!status_code)
		big->env = do_env("OLDPWD", str[1][1], big->env, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_biggertab(str[1], aux);
	free(aux);
	big->env = do_env("PWD", str[1][2], big->env, 3);
	ft_tabfree(&str[1]);
	return (status_code);
}

int	recoded_builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}

int	recoded_builtin_echo(t_list *cmd)
{
	int		newline;
	int		i[2];
	char	**argv;
	t_little	*node;

	i[0] = 0;
	i[1] = 0;
	newline = 1;
	node = cmd->content;
	argv = node->command;
	while (argv && argv[++i[0]])
	{
		if (!i[1] && !ft_strncmp(argv[i[0]], "-n", 2) && \
			(ft_countchar(argv[i[0]], 'n') == \
			(int)(ft_strlen(argv[i[0]]) - 1)))
			newline = 0;
		else
		{
			i[1] = 1;
			ft_putstr_fd(argv[i[0]], 1);
			if (argv[i[0] + 1])
				ft_putchar_fd(' ', 1);
		}
	}
	return (write(1, "\n", newline) == 2);
}

int	recoded_builtin_export(t_big *big)
{
	int		ij[2];
	int		pos;
	char	**argv;

	argv = ((t_little *)big->commands->content)->command;
	if (ft_tablen(argv) >= 2)
	{
		ij[0] = 1;
		while (argv[ij[0]])
		{
			pos = var_in_envp(argv[ij[0]], big->env, ij);
			if (pos == 1)
			{
				free(big->env[ij[1]]);
				big->env[ij[1]] = ft_strdup(argv[ij[0]]);
			}
			else if (!pos)
				big->env = ft_biggertab(big->env, argv[ij[0]]);
			ij[0]++;
		}
	}
	return (0);
}

int	recoded_builtin_unset(t_big *big)
{
	char	**argv;
	char	*aux;
	int		ij[2];

	ij[0] = 0;
	argv = ((t_little *)big->commands->content)->command;
	if (ft_tablen(argv) >= 2)
	{
		while (argv[++ij[0]])
		{
			if (argv[ij[0]][ft_strlen(argv[ij[0]]) - 1] != '=')
			{
				aux = ft_strjoin(argv[ij[0]], "=");
				free(argv[ij[0]]);
				argv[ij[0]] = aux;
			}
			if (var_in_envp(argv[ij[0]], big->env, ij))
				ft_tab_row_n_replace(&big->env, NULL, ij[1]);
		}
	}
	return (0);
}