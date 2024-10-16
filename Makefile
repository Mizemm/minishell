# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mizem <mizem@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 22:27:04 by abdennac          #+#    #+#              #
#    Updated: 2024/10/16 23:52:35 by mizem            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -fsanitize=address #-Wall -Wextra -Werror 
LDFLAGS = -lreadline
MINISHELL_C = minishell.c
UTILS_C = parsing/clear.c parsing/parser.c parsing/parsing_utils.c parsing/lexer.c parsing/expand.c parsing/expand_utils.c parsing/lexer_utils.c parsing/lexer_syntax.c parsing/lexer_type.c parsing/parsing_counters.c parsing/lexer_relex.c parsing/parsing_fillers.c\
			execution/simple_exec.c execution/execution.c execution/redirections.c execution/exec_utils.c execution/heredoc.c execution/heredoc_expand.c \
			builtins/mini_cd.c builtins/export_utils.c builtins/mini_unset.c builtins/mini_echo.c builtins/mini_exit.c builtins/mini_pwd.c builtins/mini_env.c builtins/mini_export.c\
			libft_utils/ft_strtrim.c libft_utils/ft_strncoco.c libft_utils/ft_lstadd_back_bonus.c libft_utils/add_node.c libft_utils/ft_isalnum.c\
			libft_utils/ft_strdup.c libft_utils/ft_atoi.c libft_utils/ft_strchr.c libft_utils/ft_strcmp.c libft_utils/ft_strjoin.c libft_utils/ft_strlen.c libft_utils/ft_split.c\
			libft_utils/ft_lstadd_back_env.c libft_utils/ft_putstr_fd.c libft_utils/ft_itoa.c libft_utils/ft_strncpy.c #signals.c\

MINISHELL_O = $(MINISHELL_C:.c=.o)
UTILS_O = $(UTILS_C:.c=.o)

all: $(NAME)

$(MINISHELL_O): minishell.h
$(UTILS_O): minishell.h

$(NAME): $(MINISHELL_O) $(UTILS_O) minishell.h
	$(CC) $(CFLAGS) $(LDFLAGS) $(MINISHELL_O) $(UTILS_O) -o minishell

clean:
	rm -rf $(MINISHELL_O) $(UTILS_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all