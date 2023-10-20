/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:55:53 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 12:01:52 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_status_code;

char	*path_expanding(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*tmp_str;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~' && \
			(i == 0 || str[i - 1] != '$'))
		{
			tmp_str = ft_substr(str, 0, i);
			path = ft_strjoin(tmp_str, var);
			free(tmp_str);
			tmp_str = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, tmp_str);
			free(tmp_str);
			free(path);
			return (path_expanding(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}

static char	*substr_var_expanding(char *str, int i, t_big *big)
{
	char	*final_str;
	int		end_i;
	char	*path;
	char	*var;

	end_i = ft_strchr_str(&str[i], "|\"\'$?>< ") + (ft_strchr("$?", str[i]) != 0);
	if (end_i == -1)
		end_i = ft_strlen(str) - 1;
	final_str = ft_substr(str, 0, i - 1);
	var = find_env(&str[i], big->env, ft_strchr_str(&str[i], "\"\'$|>< "));
	if (!var && str[i] == '$')
		var = ft_itoa(big->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(g_status_code);
	path = ft_strjoin(final_str, var);
	free(final_str);
	final_str = ft_strjoin(path, &str[i + end_i]);
	free(var);
	free(path);
	free(str);
	return (final_str);
}

char	*var_expanding(char *str, int i, int quotes[2], t_big *big)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1] \
		&& ((ft_strchr_str(&str[i + 1],\ "/~%^{}:; ") && !quotes[1]) \
		|| (ft_strchr_str(&str[i + 1], "/~%^{}:;\"") && quotes[1])))
			return (var_expanding(substr_var_expanding(str, ++i, big), -1, quotes, big));
	}
	return (str);
}
