/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsl <rsl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:54:52 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/19 22:42:58 by rsl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	status_code;

//gestion du bigstruct : nouvelles lignes, affichage de l'user, couleurs si besoin, etc

static char	*get_home(t_big big)
{
	char	*data;
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_strdup("∅ ");
	home = find_env("HOME", big.env, 4);
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		data = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(data);
	}
	free(home);
	home = ft_strjoin(BLUE, pwd);
	free(pwd);
	pwd = ft_strjoin(home, " ");
	free(home);
	home = ft_strjoin(" ", pwd);
	free(pwd);
	pwd = ft_strjoin(home, DEFAULT);
	free(home);
	return (pwd);
}

static char	*get_user(t_big big)
{
	char	**user;
	char	*data1;
	char	*data2;

	user = NULL;
	data2 = NULL;
	get_user_util(&user, "/usr/bin/whoami", "whoami", big.env);
	if (!user)
		user = ft_biggertab(user, "guest");
	if (!ft_strncmp(user[0], "root", 4))
		data2 = ft_strjoin(NULL, RED);
	else
		data2 = ft_strjoin(NULL, WHITE);
	data1 = ft_strjoin(data2, *user);
	free(data2);
	ft_tabfree(&user);
	return (data1);
}

char	*custom_prompt(t_big big)
{
	char	*data1;
	char	*data2;
	char	*str;
	data1 = get_user(big);
	data2 = ft_strjoin(data1, "@minishell"); //on join user et minishell
	free(data1);
	str = get_home(big);
	data1 = ft_strjoin(data2, str); //on join le home en plus
	free(str);
	free(data2);
	if (!status_code || status_code == -1) //on check le status
		data2 = ft_strjoin(data1, BLUE); //blue
	else
		data2 = ft_strjoin(data1, RED); //red
	free(data1);
	data1 = ft_strjoin(data2, "$ "); //on ajoute le $
	free(data2);
	data2 = ft_strjoin(data1, DEFAULT);
	free(data1);
	return (data2);
}
