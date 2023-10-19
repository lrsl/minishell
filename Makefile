SRC =	srcs/builtins_list.c \
	srcs/builtins_management.c \
	srcs/env_management.c \
	srcs/error_management.c \
	srcs/expander_management.c \
	srcs/f_exec_mainpart.c \
	srcs/f_exec_pathcmd_management.c \
	srcs/f_heredoc.c \
	srcs/fd_management.c \
	srcs/little_struct_management_1.c \
	srcs/little_struct_management_2.c \
	srcs/parsing_management.c \
	srcs/prompt_management.c \
	srcs/signal_management.c \
	srcs/struct_management.c \
	srcs/triming_management_1.c \
	srcs/triming_management_2.c \
	srcs/utils/ft_lst_utils.c \
	srcs/utils/ft_putstr_fd_newline.c \
	srcs/utils/ft_puttab_fd.c \
	srcs/utils/ft_split.c \
	srcs/utils/ft_str_utils.c \
	srcs/utils/ft_strchr.c \
	srcs/utils/ft_strjoin.c \
	srcs/utils/ft_tab_utils.c \
	srcs/utils/ft_user_utils.c \
	srcs/utils/ft_itoa.c \
	srcs/utils/ft_atoi.c \
	srcs/utils/ft_malloc.c \
	srcs/utils/ft_utils.c \
	srcs/main.c \

OBJ = $(SRC:.c=.o)

NAME = minishell
CC = cc
# GNL = ./get_next_Line
RDLINE_FLAGS = -L /usr/lib/x86_64-linux-gnu -lreadline
CFLAGS = -g # -Wall -Wextra -Werror
RM = rm -f
INCS = -I ./include

GREY = \e[0;30m
RED = \e[0;31m
GREEN = \e[0;32m

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# $(GNL):
# 		@make clean -C $(LIBFTDIR) 

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) -o $(NAME) $(RDLINE_FLAGS)

clean :
	@echo "$(RED) Cleaning files..."
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean : clean
	@echo -n "$(RED)"
	@echo " Cleaning binaries..."
	@$(RM) $(NAME)

re : fclean all
	@echo "$(GREEN) re-make finish"

.PHONY : all clean fclean re
