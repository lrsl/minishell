/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:21:17 by rroussel          #+#    #+#             */
/*   Updated: 2023/10/20 12:13:16 by rroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END 0
# define WRITE_END 1

# define DEFAULT "\001\033[0;39m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define BLUE "\001\033[1;94m\002"
# define WHITE "\001\033[0;97m\002"

# include <stddef.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

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
	char	*path;
	int		infile;
	int		outfile;
}			t_little;


enum	e_error_enum
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 6,
	DUPERR = 7,
	FORKERR = 8,
	PIPERR = 9,
	PIPENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13
};

///////////////////* fonction */////////////////////

int				ft_atoi(const char *nptr);

char			*ft_itoa(int n);

int				ft_lstsize(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void*));
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *newnode);

void			*ft_memset(void *str, int c, size_t n);
void			*ft_calloc(size_t nb, size_t size);

int				ft_putstr_fd_newline(char *s, int fd);

int				ft_isdigit(int c);
int				ft_isspace(char c);

size_t			ft_strlen_static(const char *s);
int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putendl_fd(char *s, int fd);
int				ft_puttab_fd(char **tab, int nl, int fd);

char			**ft_split(char const *s, char c);

size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_countchar(char *str, char c);

char			*ft_strchr(const char *str, int c);
int				ft_strchr_n(const char *str, int c);
int				ft_strchr_str(const char *str, char *str2);

char			*ft_strjoin(char const *s1, char const *s2);

int				ft_tablen(char **tab);
char			**ft_duptab(char **tab);
void			ft_tabfree(char ***tab);
char			**ft_biggertab(char **in, char *newstr);
char			**ft_tab_row_n_replace(char ***big, char **new, int index);

void			get_user_util(char ***out, char *full, char *av, char **env);

int				ft_isdigit(int c);
int				ft_isspace(char c);

int				recoded_builtin_cd(t_big *big);
int				recoded_builtin_pwd(void);
int				recoded_builtin_echo(t_list *cmd);
int				recoded_builtin_export(t_big *big);
int				recoded_builtin_unset(t_big *big);

int				builtin(t_big *big, t_list *cmd, int *is_exit, int n);
int				verif_builtin(t_little *node);

int				var_env(char *av, char **env, int tab[2]);
char			*find_env(char *var, char **env, int n);
char			**do_env(char *str, char *value, char **env, int n);

void			*error_function(int err_type, char *param, int err);
void			free_function(void *data);
int				ft_atoi2(const char *nptr, long *nbr);
int				recoded_builtin_exit(t_list *cmd, int *is_exit);
void			cd_error(char **str[2]);

char			*path_expanding(char *str, int i, int quotes[2], char *var);
char			*var_expanding(char *str, int i, int quotes[2], t_big *big);

void			child_process_builtin(t_big *bigstruct, t_little *node, int len, t_list *command);
void			*child_process(t_big *bigstruct, t_list *command, int fd[2]);
void			forking_exec(t_big *bigstruct, t_list *command, int fd[2]);
void			*forking_verif(t_big *bigstruct, t_list *command, int fd[2]);
void			*main_exec(t_big *bigstruct, t_list *command);

void			access_command(t_big *bigstruct, t_list *command, char **s, char *path);

int				get_fd(int oldfd, char *path, int flags[2]);
t_little		*manage_outfile_1(t_little *node, char **args, int *i);
t_little		*manage_outfile_2(t_little *node, char **args, int *i);
t_little		*manage_infile_1(t_little *node, char **args, int *i);
t_little		*manage_infile_2(t_little *node, char **args, int *i);

t_list			*put_in_nodes(char **tab_of_args, int i);

char			*quote_trim(char const *s1, int quote_simple, int quote_double);

char			**final_split(char **tab, t_big *big);
void			*args_parsing(char **tab, t_big *big);
void			*args_verif(char *out, t_big *big);

char			*custom_prompt(t_big big);

int				ft_here_doc(char *str[2], char *aux[2]);
char			*ft_here_doc_str(char *str[2], size_t len, char *limit, char *trigger);

void			signal_management(int signal);

t_big			fill_struct(t_big bigstruct, char *str, char **av);
void			ft_getpid(t_big *bigstruct);
t_big			struct_init(char **av, char **env);

char			**trim1(char const *str, char *target);

char			**trim2(char const *s, char *target);

char			*get_next_line(int fd);
char			*gnl_shrink_buffer(char *buf, char *line);
char			*gnl_expand_buffer(char *buf, int fd);
char			*gnl_newread(int fd);

size_t			gnl_strlen(const char *s);
char			*gnl_substr(char const *s, unsigned int start, size_t len);
size_t			gnl_strlcpy(char *dst, const char *src, size_t size);
int				gnl_strchr_i(const char *s, int c);
size_t			gnl_strlcat(char *dst, const char *src, size_t size);


////////////////////////////////////////////////////

#endif