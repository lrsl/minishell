/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:54:58 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 13:11:02 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status_code;

char	**final_split(char **tab, t_big *big)
{
	char	**subsplit;
	int		i;
	int		quotes[2];

	i = -1;
	while (tab && tab[++i])
	{
		tab[i] = var_expanding(tab[i], -1, quotes, big);
		tab[i] = path_expanding(tab[i], -1, quotes, \
		find_env("HOME", big->env, 4));
		subsplit = trim2(tab[i], "<|>");
		ft_tab_row_n_replace(&tab, subsplit, i);
		i += ft_tablen(subsplit) - 1;
		ft_tabfree(&subsplit);
	}
	return (tab);
}

void	*args_parsing(char **tab, t_big *big)
{
	int	trigger;
	int	i;

	trigger = 0;
	big->commands = put_in_nodes(final_split(tab, big), -1);
	if (!big->commands)
		return (big);
	i = ft_lstsize(big->commands);
	g_status_code = builtin(big, big->commands, &trigger, 0);
	while (i-- > 0)
		waitpid(-1, &g_status_code, 0);
	if (!trigger && g_status_code == 13)
		g_status_code = 0;
	if (g_status_code > 255)
		g_status_code = g_status_code / 255;
	if (tab && trigger)
	{
		ft_lstclear(&big->commands, free_function);
		return (NULL);
	}
	return (big);
}

void	*args_verif(char *out, t_big *big)
{
	char		**tab;
	t_little	*node;

	if (!out)
	{
		printf("exit\n");
		return (NULL);
	}
	if (out[0] != '\0')
		add_history(out);
	tab = trim1(out, " ");
	free(out);
	if (!tab)
		error_function(QUOTE, NULL, 1);
	if (!tab)
		return ("");
	big = args_parsing(tab, big);
	if (big && big->commands)
		node = big->commands->content;
	if (big && big->commands && node && node->command \
	&& ft_lstsize(big->commands) == 1)
		big->env = do_env("_", node->command[ft_tablen(node->command) - 1], \
		big->env, 1);
	if (big && big->commands)
		ft_lstclear(&big->commands, free_function);
	return (big);
}
