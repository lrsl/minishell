// do the builtins


//checker pour savoir si c'est un builtin ou pas
int	verif_builtin(t_little *node)
{
	int		l;

	if (!node->full_cmd)
		return (0);
	if ((node->full_cmd && ft_strchr(*node->full_cmd, '/')) || (node->full_path && \
		ft_strchr(node->full_path, '/')))
		return (0);
	l = ft_strlen(*node->full_cmd);
	if (!ft_strncmp(*node->full_cmd, "pwd", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "env", l) && l == 3)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "cd", l) && l == 2)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "export", l) && l == 6)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "unset", l) && l == 5)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "echo", l) && l == 4)
		return (1);
	if (!ft_strncmp(*node->full_cmd, "exit", l) && l == 4)
		return (1);
	return (0);
}