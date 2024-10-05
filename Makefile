# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mizem <mizem@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 22:27:04 by abdennac          #+#    #+#              #
#    Updated: 2024/10/05 17:38:10 by mizem            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

MINISHELL_C = minishell.c
UTILS_C = parsing/clear.c parsing/parser.c parsing/parsing_utils.c execution/simple_exec.c parsing/lexer.c parsing/expand.c\
			execution/execution.c execution/redirections.c execution/exec_utils.c libft_utils/ft_strtrim.c libft_utils/ft_strncoco.c\
			libft_utils/pipe_split.c libft_utils/ft_lstadd_back_bonus.c builtins/mini_cd.c libft_utils/add_node.c\
			libft_utils/ft_isalnum.c libft_utils/ft_strdup.c \
			libft_utils/ft_atoi.c libft_utils/ft_strchr.c libft_utils/ft_strcmp.c builtins/mini_echo.c builtins/mini_exit.c builtins/mini_pwd.c \
			builtins/mini_env.c libft_utils/ft_strjoin.c libft_utils/ft_strlen.c libft_utils/ft_split.c\
			builtins/mini_export.c

MINISHELL_O = $(MINISHELL_C:.c=.o)
UTILS_O = $(UTILS_C:.c=.o)

all: $(MINISHELL)

$(MINISHELL_O): minishell.h
$(UTILS_O): minishell.h

$(MINISHELL): $(MINISHELL_O) $(UTILS_O) minishell.h
	$(CC) $(CFLAGS) $(MINISHELL_O) $(UTILS_O) -o minishell -lreadline

clean:
	rm -rf $(MINISHELL_O) $(UTILS_O)

fclean: clean
	rm -rf $(MINISHELL)

re: fclean all 