# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abdennac <abdennac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 22:27:04 by abdennac          #+#    #+#              #
#    Updated: 2024/08/27 09:21:26 by abdennac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL = minishell
CC = cc
CFLAGS = #-Wall -Wextra -Werror #-fsanitize=address

MINISHELL_C = minishell.c
UTILS_C = parser.c execution/execution.c execution/redirections.c utils/pipe_split.c \
			utils/ft_lstadd_back_bonus.c \
			utils/quotes_counter.c utils/ft_isalnum.c utils/ft_strdup.c \
			utils/ft_strchr.c utils/ft_strcmp.c builtins/mini_echo.c builtins/mini_pwd.c \
			utils/ft_strjoin.c utils/ft_strlen.c \

MINISHELL_O = $(MINISHELL_C:.c=.o)
UTILS_O = $(UTILS_C:.c=.o)

all: $(MINISHELL)

$(MINISHELL): $(MINISHELL_O) $(UTILS_O) minishell.h
	$(CC) $(CFLAGS) $(MINISHELL_O) $(UTILS_O) -o minishell -lreadline

clean:
	rm -rf $(MINISHELL_O) $(UTILS_O)

fclean: clean
	rm -rf $(MINISHELL)

re: fclean all