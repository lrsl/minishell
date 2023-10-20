# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rroussel <rroussel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 16:19:57 by rroussel          #+#    #+#              #
#    Updated: 2023/10/20 12:13:10 by rroussel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_CYAN=\033[0;36m
COLOUR_END=\033[0m

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
	srcs/utils/get_next_line.c \
	srcs/utils/get_next_line_utils.c \
	srcs/main.c \

OBJ = $(SRC:.c=.o)

NAME = minishell
CC = cc
RDLINE_FLAGS = -L /usr/lib/x86_64-linux-gnu -lreadline
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INCS = -I ./include

all : $(NAME)

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@sleep .025
	@printf "\033[1A"
	@printf "\033[K"

$(NAME): $(OBJ)
	@echo "$(COLOUR_CYAN)\
	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝  by rroussel & anmassy$(COLOUR_END)"
                                                                   
	@$(CC) $(CFLAGS) $(INCS) $(OBJ) -o $(NAME) $(RDLINE_FLAGS)
	@echo "↪ Finished, $(COLOUR_BLUE)minishell$(COLOUR_END) $(COLOUR_GREEN)compiled$(COLOUR_END)"

clean :
	@echo "Cleaning files..."
	@$(RM) $(OBJ) $(OBJ_BONUS)
	@echo "↪ Finished, $(COLOUR_BLUE)files$(COLOUR_END) $(COLOUR_RED)cleaned$(COLOUR_END)"
	
fclean : clean
	@echo "Cleaning binaries..."
	@$(RM) $(NAME)
	@echo "↪ Finished, $(COLOUR_BLUE)binaries$(COLOUR_END) $(COLOUR_RED)cleaned$(COLOUR_END)"
	
re : fclean all
	@echo "↪ Finished, $(COLOUR_BLUE)re-make$(COLOUR_END) $(COLOUR_GREEN)done$(COLOUR_END)"

.PHONY : all clean fclean re
