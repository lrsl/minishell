#ifndef MINISHELL_H

# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_big
{
	t_list	*commands;
	char	**env;
	pid_t	pid;
}			t_big;

typedef struct s_little
{
	char	**command;
	char	**path;
	int		infile;
	int		outfile;
}			t_little;


enum
{
	XERR = 1,
	YERR = 2,
	ZERR = 3
};