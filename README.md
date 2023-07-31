# minishellsujet

	https://cdn.intra.42.fr/pdf/pdf/96051/en.subject.pdf
Bash reference manual
	https://www.gnu.org/software/bash/manual/bash.html
variables en bash
	https://riptutorial.com/bash/topic/4797/internal-variables
signal
	https://www.tutorialspoint.com/c_standard_library/c_function_signal.htm
readline
	https://man7.org/linux/man-pages/man3/readline.3.html
various resources
	https://github.com/pasqualerossi/Minishell_Resources
	https://achrafbelarif.medium.com/42cursus-minishell-29cd25f972e6
	https://gitlab.com/madebypixel02/minishell#installation
	https://minishell.simple.ink/

Global variable: we need it to control the signals we cxan have with "Ctrl-C" or "Ctrl-\". It has to update a variable (je l'ai appelee "status_code"), so we can use it in a function (genre "ft_signal").

DIR variable: se renseigner sur comment ca fonctionne exactrement pour naviguer avec ce type

-------------------------

What to do in order:
1. lexer
2. expander
3. parser
4. executor

-------------------------
-------------------------

LEXER & EXPANDER
#Ce que ca doit faire:
- expending environment variables
- expending user directory
- split input string into small tokens to better handle
	- pipes
	- redirection
	- expansion

#Comment le faire, to do so:
-> read from stdin
-> trim (use a finction to split the string, depending of spaces, quotes, etc)
-> trim again (use a function to split each substrting again, taking into account " | ", " " ", " </> ")

Example:
string: echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
trim1: {echo, "hello      there", how, are, 'you 'doing?, $USER, |wc, -l, >outfile, NULL}
trim2: {echo, "hello      there", how, are, 'you 'doing?, pixel, |, wc, -l, >, outfile, NULL}

On lit le struct, et on divise en utilisant 2 fonctions de trim, pour separer chaque element.
--> nous donne un tableau a 2 dimensions!


-------------------------
-------------------------


PARSER
- we need to create 2 structures to store the data:
	- a big one (pour stocker les infos generales genre la liste chainee des commandes, variable environnemment etc)
	- a smaller one (qui va etre cree pour chaque commande et qui contient la commande, son path, le in?out file)

En gros : une "BIG" structure qui contient les infos generales mais aussi une liste chainee de "SMALL" structures qui correspondent a chaque commande.
			-->>> VOIR SCREENSHOT DANS LE DOSSIER

-> on utilise le tableau a 2 dimensions de l'expander (vu au dessus), et le parser va choper les infos du tableau pour remplir les deux structures:

#Les etapes:
- iterer sur tout le tableau cree par l'expander
- quand il y a une redirection, regarde le fd associe et verifie que tout est valide/open
- quand il y a un pipe, il va creer un nouveau node ("SMALL" struct pour chaue commande)
- dans tous les cas va stocker tout ce qu'il y a dans une variable de "SMALL STRUCT" (la variable appelee "full_cmd" dans le screenshot)

Ce que ca donne avec la phrase d'exemple au dessus:

+++++++++++++

/ cmds:
   // cmd 1:
     //// infile: 0 (default)
     //// outfile: 1 (redirected to pipe)
     //// full_path: NULL (because echo is a builtin)
     //// full_cmd: {echo, hello there, how, are, you doing?, pixel, NULL}
   // cmd 2:
     //// infile: 0 (contains output of previous command)
     //// outfile: 3 (fd corresponding to the open file 'outfile')
     //// full_path: /bin/wc
     //// full_cmd: {wc, -l, NULL}
/ envp: (envp from main)
/ pid: process ID of current instance
/ g_status: 0 (if last command exits normally)

+++++++++++++



-------------------------
-------------------------


EXECUTOR 

En gros
- j'utilise des processes child pour lancer soit des commandes builtin ou des commandes reelles
- je redirige stdin/stdout
- si j'ai un full path c'est super je lance avec exec, sinon je prends le relative path et je cree le full path en utilisant l'environment
- je gere les status exit des commandes et quand elles ont toutes fini, je lance un nouveau struct pres a recevoir une nouvelle commande!

-------------------------
-------------------------
